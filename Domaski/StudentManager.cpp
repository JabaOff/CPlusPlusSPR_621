// student_db.cpp — База даних студентів, C++17
// g++ -std=c++17 -O2 -o student_db student_db.cpp && ./student_db
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <random>
#include <cctype>
#include <set>
#include <unordered_map>

// ════════════════════════════════════════════════════════════════════
// 1. ЕНУМИ ТА СТРУКТУРИ
// ════════════════════════════════════════════════════════════════════
namespace db {

    enum class Fac { CS, MATH, PHYS, ECO, LAW, MED, ENG, LING, _N };
    enum class Status { ACTIVE, SUSPENDED, GRADUATED, WITHDRAWN, LEAVE, _N };
    enum class Form { FULL, PART, DIST, EVEN, _N };

    const char* fac_name(Fac f) { static const char* n[] = { "Комп'ютерні науки","Математика","Фізика","Економіка","Право","Медицина","Інженерія","Мовні" }; return n[f]; }
    const char* st_name(Status s) { static const char* n[] = { "Активний","Виключений","Завершив","Самовільний","Відпустка" }; return n[s]; }
    const char* form_name(Form f) { static const char* n[] = { "Очна","Змішана","Дистанційна","Вечірня" }; return n[f]; }

    struct Student {
        int64_t id = 0;
        std::string first, last, mid;
        int  yob = 0;
        Fac  fac = Fac::CS;
        std::string group;
        int  course = 1;
        Form form = Form::FULL;
        double gpa = 0.0;
        Status status = Status::ACTIVE;
        std::string email, phone, city, addr;
        int64_t scholarship = 0;
        int  credits = 0;
        int  y_start = 0;
        int64_t created = 0, updated = 0;

        std::string full() const { return last + " " + first + (mid.empty() ? "" : " " + mid); }
        int age() const {
            int y = std::chrono::year{ std::chrono::system_clock::now().time_since_epoch().count() / 31557600 }.year();
            return y - yob;
        }
    };

    struct Grade { int64_t sid; std::string subject; double score; std::string sem; };
    struct LogEntry { int64_t ts; std::string op; std::string detail; };
    struct Stats {
        int total = 0, active = 0;
        double avg = 0, top = 0, bottom = 10;
        int credits = 0;
        int64_t scholarship = 0;
        int per_fac[8] = {};
        int per_cr[6] = {};
        int per_st[5] = {};
        std::string top_name, bot_name;
    };

    // ════════════════════════════════════════════════════════════════════
    // 2. УТИЛІТИ
    // ════════════════════════════════════════════════════════════════════
    static std::string trim(const std::string& s) {
        auto a = s.find_first_not_of(" \t\n\r"), b = s.find_last_not_of(" \t\n\r");
        return a == std::string::npos ? "" : s.substr(a, b - a + 1);
    }
    static std::string low(const std::string& s) {
        std::string r = s; for (char& c : r) c = (char)std::tolower((unsigned char)c); return r;
    }
    static std::vector<std::string> split(const std::string& s, char d) {
        std::vector<std::string> v; std::string c;
        for (char ch : s) { if (ch == d) { v.push_back(trim(c));c.clear(); } else c += ch; }
        v.push_back(trim(c)); return v;
    }
    static int64_t now() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
    static std::string ts(int64_t t) {
        if (!t) return "—";
        auto tt = std::chrono::system_clock::from_time_t((time_t)t);
        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &tt);
#else
        localtime_r(&tt, &tm);
#endif
        char buf[32]; std::strftime(buf, 32, "%Y-%m-%d %H:%M:%S", &tm);
        return std::string(buf);
    }

    // ════════════════════════════════════════════════════════════════════
    // 3. WAL
    // ════════════════════════════════════════════════════════════════════
    struct WalRec { int64_t lsn, sid; std::string op, data; };
    class Wal {
        std::ofstream out_; size_t pend_ = 0;
        std::mutex mtx_;
    public:
        void open(const std::string& p) { out_.open(p, std::ios::app | std::ios::binary); }
        void close() { flush(); out_.close(); }
        void log(const std::string& op, int64_t sid, const std::string& data) {
            std::lock_guard<std::mutex> lk(mtx_);
            out_ << pend_++ << "|" << op << "|" << sid << "|" << data << "\n";
            out_.flush();
        }
        void flush() {}
        std::vector<WalRec> read() {
            std::vector<WalRec> r; std::ifstream in("student_db.wal");
            if (!in) return r;
            std::string l;
            while (std::getline(in, l)) {
                auto p = split(l, '|');
                if (p.size() >= 4) { WalRec w; w.lsn = std::stoll(p[0]); w.op = p[1]; w.sid = std::stoll(p[2]); w.data = p[3]; r.push_back(w); }
            }
            return r;
        }
    };

    // ════════════════════════════════════════════════════════════════════
    // 4. ГЛАВНА БАЗА
    // ════════════════════════════════════════════════════════════════════
    class Database {
        std::vector<Student> stu_;
        std::unordered_map<int64_t, int> idx_;
        std::map<std::string, std::vector<int>> name_idx_;
        std::vector<Grade> grades_;
        std::vector<LogEntry> log_;
        Wal wal_;
        int64_t nid_ = 1;
        std::shared_mutex mtx_;
        std::string path_ = "student_db.dat";

        void rebuild() {
            idx_.clear(); name_idx_.clear();
            for (int i = 0;i < (int)stu_.size();i++) {
                idx_[stu_[i].id] = i;
                name_idx_[low(stu_[i].last)].push_back(i);
            }
        }

        void load() {
            std::ifstream in(path_);
            if (!in) return;
            stu_.clear();
            std::string l;
            while (std::getline(in, l)) {
                auto p = split(l, ';');
                if (p.size() < 15) continue;
                Student s;
                s.id = std::stoll(p[0]);
                s.first = trim(p[1]); s.last = trim(p[2]); s.mid = trim(p[3]);
                s.yob = std::stoi(p[4]);
                s.fac = static_cast<Fac>(std::stoi(p[5]));
                s.group = trim(p[6]);
                s.course = std::stoi(p[7]);
                s.form = static_cast<Form>(std::stoi(p[8]));
                s.gpa = std::stod(p[9]);
                s.status = static_cast<Status>(std::stoi(p[10]));
                s.email = trim(p[11]);
                s.phone = trim(p[12]);
                s.city = trim(p[13]);
                s.scholarship = std::stoll(p[14]);
                if (p.size() > 15) s.credits = std::stoi(p[15]);
                if (p.size() > 16) s.created = std::stoll(p[16]);
                nid_ = std::max(nid_, s.id + 1);
                stu_.push_back(s);
            }
            rebuild();
        }

        void save() {
            std::ofstream out(path_);
            for (auto& s : stu_) {
                out << s.id << ";" << s.first << ";" << s.last << ";" << s.mid << ";"
                    << s.yob << ";" << (int)s.fac << ";" << s.group << ";"
                    << s.course << ";" << (int)s.form << ";"
                    << std::fixed << std::setprecision(2) << s.gpa << ";"
                    << (int)s.status << ";" << s.email << ";" << s.phone << ";"
                    << s.city << ";" << s.scholarship << ";" << s.credits << ";" << s.created << "\n";
            }
        }

    public:
        // ── Життєвий цикл ──────────────────────────────────────────────
        void open() {
            wal_.open("student_db.wal");
            load();
            std::cout << "\n  База відкрита. Записів: " << stu_.size() << "\n";
        }
        void close() {
            save(); wal_.close();
            std::cout << "  Дані збережено. База закрита.\n";
        }

        // ── INSERT ──────────────────────────────────────────────────────
        int64_t add(const Student& s0) {
            std::unique_lock<std::shared_mutex> lk(mtx_);
            Student s = s0; s.id = nid_++; s.created = now(); s.updated = s.created;
            for (auto& x : stu_) if (x.email == s.email && !s.email.empty())
                throw std::runtime_error("Дублікат email: " + s.email);
            stu_.push_back(s);
            log_.push_back({ now(),"INSERT","id=" + std::to_string(s.id) + " " + s.full() });
            wal_.log("INSERT", s.id, s.full());
            return s.id;
        }

        // ── UPDATE ──────────────────────────────────────────────────────
        bool update(int64_t id, const Student& u) {
            std::unique_lock<std::shared_mutex> lk(mtx_);
            auto it = idx_.find(id);
            if (it == idx_.end()) return false;
            auto& s = stu_[it->second];
            s.first = u.first; s.last = u.last; s.mid = u.mid;
            s.yob = u.yob; s.fac = u.fac; s.group = u.group;
            s.course = u.course; s.form = u.form; s.gpa = u.gpa;
            s.status = u.status; s.email = u.email; s.phone = u.phone;
            s.city = u.city; s.scholarship = u.scholarship; s.credits = u.credits;
            s.updated = now();
            log_.push_back({ now(),"UPDATE","id=" + std::to_string(id) });
            wal_.log("UPDATE", id, "updated");
            return true;
        }

        // ── DELETE ──────────────────────────────────────────────────────
        bool remove(int64_t id) {
            std::unique_lock<std::shared_mutex> lk(mtx_);
            auto it = idx_.find(id);
            if (it == idx_.end()) return false;
            int pos = it->second;
            stu_[pos] = std::move(stu_.back());
            stu_.pop_back();
            log_.push_back({ now(),"DELETE","id=" + std::to_string(id) });
            wal_.log("DELETE", id, "");
            rebuild();
            return true;
        }

        // ── FIND ────────────────────────────────────────────────────────
        Student* find(int64_t id) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            auto it = idx_.find(id);
            return it != idx_.end() ? &stu_[it->second] : nullptr;
        }

        // ── ПОШУК ЗА ІМЕНЕМ ────────────────────────────────────────────
        std::vector<Student> search_name(const std::string& q) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::vector<Student> r;
            std::string ql = low(trim(q));
            for (auto& s : stu_)
                if (low(s.full()).find(ql) != std::string::npos) r.push_back(s);
            return r;
        }

        // ── ФІЛЬТР ──────────────────────────────────────────────────────
        struct Filter {
            Fac fac = Fac::CS; Status st = Status::ACTIVE;
            int cr = 0; double min_g = 0, max_g = 10; bool use_g = false;
            std::string group;
        };
        std::vector<Student> query(const Filter& f) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::vector<Student> r;
            for (auto& s : stu_) {
                if (s.fac != f.fac) continue;
                if (s.status != f.st) continue;
                if (f.cr && s.course != f.cr) continue;
                if (f.use_g && (s.gpa<f.min_g || s.gpa>f.max_g)) continue;
                if (!f.group.empty() && s.group.find(f.group) == std::string::npos) continue;
                r.push_back(s);
            }
            return r;
        }

        // ── СОРТУВАННЯ ──────────────────────────────────────────────────
        std::vector<Student> sorted_by(int mode, bool desc) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            auto v = stu_;
            std::function<bool(Student&, Student&)> cmp;
            switch (mode) {
            case 0: cmp = [](auto& a, auto& b) {return a.last < b.last;}; break;
            case 1: cmp = [](auto& a, auto& b) {return a.gpa < b.gpa;}; break;
            case 2: cmp = [](auto& a, auto& b) {return a.yob > b.yob;}; break;
            case 3: cmp = [](auto& a, auto& b) {return a.course < b.course;}; break;
            case 4: cmp = [](auto& a, auto& b) {return a.credits < b.credits;}; break;
            default:cmp = [](auto& a, auto& b) {return a.id < b.id;}; break;
            }
            if (desc) std::sort(v.begin(), v.end(), [&](auto& a, auto& b) {return cmp(b, a);});
            else     std::sort(v.begin(), v.end(), cmp);
            return v;
        }

        // ── СТАТИСТИКА ──────────────────────────────────────────────────
        Stats stats() {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            Stats s; s.total = (int)stu_.size();
            double sum = 0;
            for (auto& x : stu_) {
                if (x.status == Status::ACTIVE) s.active++;
                sum += x.gpa;
                s.credits += x.credits;
                s.scholarship += x.scholarship;
                s.per_fac[(int)x.fac]++;
                s.per_cr[x.course]++;
                s.per_st[(int)x.status]++;
            }
            if (s.total) {
                s.avg = sum / s.total; auto v = sorted_by(1, false);
                s.top = v[0].gpa; s.top_name = v[0].full();
                s.bottom = v.back().gpa; s.bot_name = v.back().full();
            }
            return s;
        }

        int count() const { return (int)stu_.size(); }
        int64_t next_id() const { return nid_; }

        // ── ЕКСПОРТ ─────────────────────────────────────────────────────
        void export_csv(const std::string& p) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::ofstream o(p);
            o << "ID;ПіБ;Рок;Факультет;Група;Курс;Форма;ГPA;Статус;Email;Тел;Місто;Стипендія;ECTS\n";
            for (auto& s : stu_) {
                o << s.id << ";" << s.full() << ";" << s.yob << ";"
                    << fac_name(s.fac) << ";" << s.group << ";" << s.course << ";"
                    << form_name(s.form) << ";" << std::fixed << std::setprecision(2) << s.gpa << ";"
                    << st_name(s.status) << ";" << s.email << ";" << s.phone << ";"
                    << s.city << ";" << s.scholarship << ";" << s.credits << "\n";
            }
            std::cout << "  Експорт → " << p << "\n";
        }

        void export_sql(const std::string& p) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::ofstream o(p);
            o << "-- Генеровано " << ts(now()) << "\n";
            o << "CREATE TABLE students (id INT, first TEXT, last TEXT, mid TEXT, "
                "yob INT, fac INT, grp TEXT, crs INT, form INT, gpa REAL, "
                "status INT, email TEXT, phone TEXT, city TEXT, sch INT, ects INT);\n\n";
            for (auto& s : stu_) {
                o << "INSERT INTO students VALUES("
                    << s.id << ",'" << s.first << "','" << s.last << "','" << s.mid << "',"
                    << s.yob << "," << (int)s.fac << ",'" << s.group << "'," << s.course << ","
                    << (int)s.form << "," << s.gpa << "," << (int)s.status << ",'" << s.email
                    << "','" << s.phone << "','" << s.city << "',"
                    << s.scholarship << "," << s.credits << ");\n";
            }
            std::cout << "  SQL-скрипт → " << p << "\n";
        }

        // ── ЛОГ ─────────────────────────────────────────────────────────
        void show_log(int n = 20) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            int s = (int)log_.size();
            for (int i = std::max(0, s - n);i < s;i++)
                std::cout << "  [" << ts(log_[i].ts) << "] " << log_[i].op << " " << log_[i].detail << "\n";
        }

        // ── ГЕНЕРАЦІЯ ДЕМО-ДАННИХ ───────────────────────────────────────
        void demo(int n = 100) {
            std::mt19937 rng(42);
            std::string fnames[] = { "Олександр","Андрій","Іван","Павло","Микола","Дмитро","Владимир","Віктор","Максим","Артем","Юрій","Олег","Володимир","Сергій","Роман","Андрій","Богдан","Тарас","Остап","Леонід","Юлія","Олена","Анна","Марія","Тетяна","Наталія","Ірина","Світлана","Оксана","Нина" };
            std::string lnames[] = { "Коваленко","Бондаренко","Ткаченко","Шевченко","Кравченко","Богданов","Мороз","Гриценко","Поліщук","Сидоренко","Литвин","Романенко","Марченко","Олійник","Барабаш","Данилюк","Гнатюк","Іваненко","Захарченко","Гаврилюк","Ткач","Петренко","Савченко","Ткаченко","Гнатченко","Бондар","Лисенко","Мельник","Слободян","Ярмоленко" };
            std::string cities[] = { "Київ","Львів","Дніпро","Одеса","Харків","Запоріжжя","Вінниця","Полтава","Чернівці","Луцьк" };
            std::string interests_pool[] = { "програмування","шахи","музика","футбол","математика","фізика","історія","малювання","гімнастика","шаховий клуб","астрономія","біологія","гірський туризм","спідкубінг","3D-друк" };

            for (int i = 0;i < n;i++) {
                Student s;
                bool fem = rng() % 2 == 0;
                s.first = fnames[rng() % 30];
                s.last = lnames[rng() % 30];
                s.mid = fnames[rng() % 30];
                s.yob = 1998 + (int)(rng() % 8);
                s.fac = static_cast<Fac>(rng() % 8);
                s.course = (int)(rng() % 5) + 1;
                s.group = (char)('A' + rng() % 8) + std::to_string((int)(rng() % 40) + 1);
                s.form = static_cast<Form>(rng() % 4);
                s.gpa = 5.5 + rng() % 500 / 100.0;
                s.status = static_cast<Status>(rng() % 5 == 0 ? (rng() % 4) + 1 : 0);
                s.email = s.first[0] + std::to_string(rng() % 10000) + "@mail.ua";
                s.phone = "+380" + std::to_string(10 + rng() % 89) + std::to_string(1000000 + rng() % 8999999);
                s.city = cities[rng() % 10];
                s.scholarship = rng() % 3000;
                s.credits = (int)(rng() % 60) + 10;
                int ni = 1 + (int)(rng() % 4);
                for (int j = 0;j < ni;j++) s.interests.push_back(interests_pool[rng() % 15]);
                try { add(s); }
                catch (...) {}
            }
            std::cout << "  Згенеровано " << n << " записів.\n";
        }

        // ── ВИСІВ ───────────────────────────────────────────────────────
        static void print_hdr() {
            std::cout << "\n";
            std::cout << std::left
                << std::setw(6) << "ID"
                << std::setw(32) << "ПІБ"
                << std::setw(6) << "Рок"
                << std::setw(22) << "Факультет"
                << std::setw(5) << "Гр."
                << std::setw(4) << "Кр."
                << std::setw(6) << "Форм."
                << std::setw(7) << "GPA"
                << std::setw(14) << "Статус"
                << std::setw(14) << "Стип."
                << std::setw(5) << "ECTS" << "\n";
            std::cout << std::string(121, '-') << "\n";
        }
        static void print_row(const Student& s) {
            std::cout << std::left
                << std::setw(6) << s.id
                << std::setw(32) << s.full()
                << std::setw(6) << s.yob
                << std::setw(22) << fac_name(s.fac)
                << std::setw(5) << s.group
                << std::setw(4) << s.course
                << std::setw(6) << form_name(s.form)
                << std::setw(7) << std::fixed << std::setprecision(2) << s.gpa
                << std::setw(14) << st_name(s.status)
                << std::setw(14) << std::to_string(s.scholarship) + "грн"
                << std::setw(5) << s.credits << "\n";
        }

        // ── ПОШУК ЗА ЗНАЧЕННЯМ ГПА ──────────────────────────────────────
        std::vector<Student> by_gpa_range(double lo, double hi) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::vector<Student> r;
            for (auto& s : stu_) if (s.gpa >= lo && s.gpa <= hi) r.push_back(s);
            return r;
        }

        // ── РАЗРОЗРОБЛЕННЯ ПО ФАКУЛЬТЕТАХ ──────────────────────────────
        void print_by_faculty() {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::cout << "\n  Розподіл за факультетами:\n";
            for (int i = 0;i < 8;i++) {
                int cnt = 0, act = 0;
                for (auto& s : stu_) { if (s.fac == (Fac)i) { cnt++; if (s.status == Status::ACTIVE) act++; } }
                std::cout << "    " << std::left << std::setw(24) << fac_name((Fac)i)
                    << cnt << " (активних: " << act << ")\n";
            }
        }

        // ── РАЗРОЗРОБЛЕННЯ ПО КУРСАХ ───────────────────────────────────
        void print_by_course() {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            std::cout << "\n  Розподіл за курсами:\n";
            for (int c = 1;c <= 5;c++) {
                int cnt = 0;
                for (auto& s : stu_) if (s.course == c) cnt++;
                std::cout << "    Курс " << c << ": " << cnt << " студентів\n";
            }
        }

        // ── ТОП-10 / БУТ-10 ─────────────────────────────────────────────
        void top_n(int n, bool best = true) {
            auto v = sorted_by(1, best);
            int lim = std::min(n, (int)v.size());
            std::cout << "\n  " << (best ? "ТОП" : "НАЙГІРСІ") << " " << lim << " за GPA:\n";
            for (int i = 0;i < lim;i++) print_row(v[i]);
        }

        // ── ПОШУК ЗА ЕМЭЙЛ ──────────────────────────────────────────────
        Student* find_email(const std::string& e) {
            std::shared_lock<std::shared_mutex> lk(mtx_);
            for (auto& s : stu_) if (s.email == e) return &s;
            return nullptr;
        }

        // ── ЗАВАНТАЖЕННЯ ІЗ CSV ─────────────────────────────────────────
        void import_csv(const std::string& path) {
            std::ifstream in(path);
            if (!in) throw std::runtime_error("Файл не знайдено: " + path);
            std::string l;
            std::getline(in, l);
            int cnt = 0;
            while (std::getline(in, l)) {
                auto p = split(l, ';');
                if (p.size() < 15) continue;
                Student s;
                s.first = trim(p[1]); s.last = trim(p[2]); s.mid = trim(p[3]);
                s.yob = std::stoi(p[4]);
                s.group = trim(p[6]);
                s.course = std::stoi(p[7]);
                s.gpa = std::stod(p[9]);
                s.email = trim(p[11]);
                s.phone = trim(p[12]);
                s.city = trim(p[13]);
                s.scholarship = std::stoll(p[14]);
                s.credits = p.size() > 15 ? std::stoi(p[15]) : 0;
                try { add(s); cnt++; }
                catch (...) {}
            }
            std::cout << "  Імпорт: завантажено " << cnt << " записів\n";
        }

        // ── АУДИТ / ЖУРНАЛ ──────────────────────────────────────────────
        size_t log_size() const { return log_.size(); }
    };

    // ════════════════════════════════════════════════════════════════════
    // 5. КОНСОЛЬНИЙ ІНТЕРФЕЙС
    // ════════════════════════════════════════════════════════════════════
    void print_menu() {
        std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║         БАЗА ДАНИХ СТУДЕНТІВ  v1.0                ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n\n";
        std::cout << "  [1]  Список усіх студентів\n";
        std::cout << "  [2]  Додати студента\n";
        std::cout << "  [3]  Знайти за ID\n";
        std::cout << "  [4]  Знайти за іменем / прізвищем\n";
        std::cout << "  [5]  Знайти за email\n";
        std::cout << "  [6]  Редагувати студента\n";
        std::cout << "  [7]  Видалити студента\n";
        std::cout << "  [8]  Фільтр за факультетом / курсом / GPA\n";
        std::cout << "  [9]  Сортувати\n";
        std::cout << "  [10] Статистика\n";
        std::cout << "  [11] Розподіл за факультетами\n";
        std::cout << "  [12] Розподіл за курсами\n";
        std::cout << "  [13] ТОП-10 / Найгірші 10\n";
        std::cout << "  [14] Експорт CSV\n";
        std::cout << "  [15] Експорт SQL\n";
        std::cout << "  [16] Імпорт CSV\n";
        std::cout << "  [17] Генерувати 100 демо-записів\n";
        std::cout << "  [18] Журнал операцій\n";
        std::cout << "  [19] Зберегти й вийти\n";
        std::cout << "  [0]  Вихід без збереження\n\n";
    }

    void input_student(Student& s, Database& db) {
        std::cout << "  Введіть дані студента:\n";
        std::string line;
        std::cout << "    Прізвище: ";  std::getline(std::cin, s.last);
        std::cout << "    Ім'я: ";      std::getline(std::cin, s.first);
        std::cout << "    По батькові: ";std::getline(std::cin, s.mid);
        std::cout << "    Рік народж.: ";std::getline(std::cin, line); s.yob = std::stoi(trim(line));
        std::cout << "    Факультет (0-7): "; std::getline(std::cin, line);
        s.fac = static_cast<Fac>(std::stoi(trim(line)));
        std::cout << "    Група: ";   std::getline(std::cin, s.group);
        std::cout << "    Курс: ";    std::getline(std::cin, line); s.course = std::stoi(trim(line));
        std::cout << "    Форма (0-3): "; std::getline(std::cin, line);
        s.form = static_cast<Form>(std::stoi(trim(line)));
        std::cout << "    GPA: ";     std::getline(std::cin, line); s.gpa = std::stod(trim(line));
        std::cout << "    Статус (0-4): "; std::getline(std::cin, line);
        s.status = static_cast<Status>(std::stoi(trim(line)));
        std::cout << "    Email: ";   std::getline(std::cin, s.email);
        std::cout << "    Телефон: "; std::getline(std::cin, s.phone);
        std::cout << "    Місто: ";   std::getline(std::cin, s.city);
        std::cout << "    Стипендія: ";std::getline(std::cin, line); s.scholarship = std::stoll(trim(line));
        std::cout << "    ECTS: ";    std::getline(std::cin, line); s.credits = std::stoi(trim(line));
    }

    int main() {
        setlocale(LC_ALL, "");
        Database db;
        db.open();
        print_menu();
        std::string cmd;
        while (true) {
            std::cout << "  > ";
            std::getline(std::cin, cmd);
            cmd = trim(cmd);
            if (cmd.empty()) continue;
            auto arg = split(cmd, ' ');
            std::string a = arg[0];

            // ── 1: ВСІ ─────────────────────────────────────────────────
            if (a == "1") {
                std::cout << "\n  Усього записів: " << db.count() << "\n\n";
                auto v = db.sorted_by(5, false);
                db.print_hdr();
                for (auto& s : v) db.print_row(s);
            }
            // ── 2: ДОДАТИ ──────────────────────────────────────────────
            else if (a == "2") {
                Student s;
                input_student(s, db);
                try {
                    int64_t id = db.add(s);
                    std::cout << "  ✓ Додано, ID=" << id << "\n";
                }
                catch (std::exception& e) {
                    std::cout << "  ✗ " << e.what() << "\n";
                }
            }
            // ── 3: ЗА ID ───────────────────────────────────────────────
            else if (a == "3") {
                if (arg.size() < 2) { std::cout << "  Введіть ID\n"; continue; }
                auto* s = db.find(std::stoll(arg[1]));
                if (!s) { std::cout << "  Не знайдено\n"; continue; }
                db.print_hdr(); db.print_row(*s);
            }
            // ── 4: ЗА ІМЕНЕМ ───────────────────────────────────────────
            else if (a == "4") {
                if (arg.size() < 2) { std::cout << "  Введіть частину імені\n"; continue; }
                auto v = db.search_name(arg[1]);
                if (v.empty()) { std::cout << "  Нічого не знайдено\n"; continue; }
                std::cout << "  Знайдено: " << v.size() << "\n\n";
                db.print_hdr();
                for (auto& s : v) db.print_row(s);
            }
            // ── 5: ЗА EMAIL ────────────────────────────────────────────
            else if (a == "5") {
                if (arg.size() < 2) { std::cout << "  Введіть email\n"; continue; }
                auto* s = db.find_email(arg[1]);
                if (!s) { std::cout << "  Не знайдено\n"; continue; }
                db.print_hdr(); db.print_row(*s);
            }
            // ── 6: РЕДАГУВАТИ ──────────────────────────────────────────
            else if (a == "6") {
                if (arg.size() < 2) { std::cout << "  Введіть ID\n"; continue; }
                int64_t id = std::stoll(arg[1]);
                auto* s = db.find(id);
                if (!s) { std::cout << "  Не знайдено\n"; continue; }
                std::cout << "  Поточні дані:\n";
                db.print_row(*s);
                Student u = *s;
                input_student(u, db);
                u.id = id;
                if (db.update(id, u)) std::cout << "  ✓ Оновлено\n";
                else std::cout << "  ✗ Помилка\n";
            }
            // ── 7: ВИДАЛИТИ ────────────────────────────────────────────
            else if (a == "7") {
                if (arg.size() < 2) { std::cout << "  Введіть ID\n"; continue; }
                int64_t id = std::stoll(arg[1]);
                if (db.remove(id)) std::cout << "  ✓ Видалено\n";
                else std::cout << "  ✗ Не знайдено\n";
            }
            // ── 8: ФІЛЬТР ──────────────────────────────────────────────
            else if (a == "8") {
                db::Filter f;
                std::string line;
                std::cout << "    Факультет (0-7, * - всі): ";
                std::getline(std::cin, line);
                if (trim(line) != "*" && !trim(line).empty())
                    f.fac = static_cast<Fac>(std::stoi(trim(line)));
                else f.fac = static_cast<Fac>(255);
                std::cout << "    Статус (0-4, * - всі): ";
                std::getline(std::cin, line);
                if (trim(line) != "*" && !trim(line).empty())
                    f.st = static_cast<Status>(std::stoi(trim(line)));
                else f.st = static_cast<Status>(255);
                auto v = db.sorted_by(5, false);
                std::vector<Student> r;
                for (auto& s : v) {
                    if (f.fac != Fac(255) && s.fac != f.fac) continue;
                    if (f.st != Status(255) && s.status != f.st) continue;
                    r.push_back(s);
                }
                std::cout << "  Результат: " << r.size() << "\n\n";
                db.print_hdr();
                for (auto& s : r) db.print_row(s);
            }
            // ── 9: СОРТУВАННЯ ──────────────────────────────────────────
            else if (a == "9") {
                int mode = 0, dir = 0;
                std::string line;
                std::cout << "    Поля: 0-Ім'я 1-GPA 2-Вік 3-Курс 4-ECTS 5-ID: ";
                std::getline(std::cin, line); mode = std::stoi(trim(line));
                std::cout << "    Напрямок: 0-ASC 1-DESC: ";
                std::getline(std::cin, line); dir = std::stoi(trim(line));
                auto v = db.sorted_by(mode, dir != 0);
                db.print_hdr();
                for (auto& s : v) db.print_row(s);
            }
            // ── 10: СТАТИСТИКА ─────────────────────────────────────────
            else if (a == "10") {
                auto st = db.stats();
                std::cout << "\n  ═══ СТАТИСТИКА ═══\n\n";
                std::cout << "    Усього:      " << st.total << "\n";
                std::cout << "    Активних:    " << st.active << "\n";
                std::cout << "    Середній:    " << std::fixed << std::setprecision(2) << st.avg << "\n";
                std::cout << "    Максимум:    " << std::fixed << std::setprecision(2) << st.top << " (" << st.top_name << ")\n";
                std::cout << "    Мінімум:     " << std::fixed << std::setprecision(2) << st.bottom << " (" << st.bot_name << ")\n";
                std::cout << "    Сумарно ECTS:" << st.credits << "\n";
                std::cout << "    Стипендії:   " << st.scholarship << " грн\n\n";
                std::cout << "    За факультетами:\n";
                for (int i = 0;i < 8;i++)
                    std::cout << "      " << std::left << std::setw(24) << fac_name((Fac)i) << st.per_fac[i] << "\n";
                std::cout << "\n    За курсами:\n";
                for (int c = 1;c <= 5;c++)
                    std::cout << "      Курс " << c << ": " << st.per_cr[c] << "\n";
                std::cout << "\n    За статусом:\n";
                for (int i = 0;i < 5;i++)
                    std::cout << "      " << std::left << std::setw(20) << st_name((Status)i) << st.per_st[i] << "\n";
            }
            // ── 11: ФАКУЛЬТЕТИ ─────────────────────────────────────────
            else if (a == "11") { db.print_by_faculty(); }
            // ── 12: КУРСИ ──────────────────────────────────────────────
            else if (a == "12") { db.print_by_course(); }
            // ── 13: ТОП ─────────────────────────────────────────────────
            else if (a == "13") {
                std::string line;
                std::cout << "    1=ТОП  0=НАЙГІРСІ: ";
                std::getline(std::cin, line);
                db.top_n(10, std::stoi(trim(line)) == 1);
            }
            // ── 14: CSV ─────────────────────────────────────────────────
            else if (a == "14") {
                std::string p = "export.csv";
                if (arg.size() > 1) p = arg[1];
                db.export_csv(p);
            }
            // ── 15: SQL ─────────────────────────────────────────────────
            else if (a == "15") {
                std::string p = "export.sql";
                if (arg.size() > 1) p = arg[1];
                db.export_sql(p);
            }
            // ── 16: ІМПОРТ ──────────────────────────────────────────────
            else if (a == "16") {
                std::string p = "import.csv";
                if (arg.size() > 1) p = arg[1];
                try { db.import_csv(p); }
                catch (std::exception& e) { std::cout << "  ✗ " << e.what() << "\n"; }
            }
            // ── 17: ДЕМО ────────────────────────────────────────────────
            else if (a == "17") { db.demo(100); }
            // ── 18: ЛОГ ─────────────────────────────────────────────────
            else if (a == "18") {
                std::cout << "\n  Журнал (" << db.log_size() << " записів):\n";
                db.show_log(30);
            }
            // ── 19: ЗБЕРЕГТИ ────────────────────────────────────────────
            else if (a == "19") {
                db.close();
                return 0;
            }
            // ── 0: ВИХІД ────────────────────────────────────────────────
            else if (a == "0") {
                std::cout << "  Вихід без збереження.\n";
                return 0;
            }
            else {
                std::cout << "  Невірний вибір: " << a << "\n";
            }
            print_menu();
        }
        return 0;
    }
