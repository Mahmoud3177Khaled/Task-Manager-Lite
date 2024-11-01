#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;


class Proccess
{
    string name, pid_str, session_n, session_num, mem_str;
    int pid, mem, sort_id;

    public:

        Proccess(string s, int srt)
        {
            sort_id = srt;

            for (int i = 0; i < s.size(); i++)
            {
                if(i <= 26)
                    name += s[i];
                else if(i <= 34)
                    pid_str += s[i];
                else if(i <= 48)
                    session_n += s[i];
                else if(i <= 63)
                    session_num += s[i];
                else if(i <= 85)
                    mem_str += s[i];
            }


            string temp;
            for (int i = 0; i < name.size(); i++)
            {
                if(name[i] != ' ')
                    temp += name[i];
            }
            name = temp;
            transform(name.begin(), name.end(), name.begin(), ::tolower);

            temp = "";
            for (int i = 0; i < pid_str.size(); i++)
            {
                if(pid_str[i] != ' ')
                    temp += pid_str[i];
            }
            pid_str = temp;
            pid = stoi(pid_str);
            
            temp = "";
            for (int i = 0; i < session_n.size(); i++)
            {
                if(session_n[i] != ' ')
                    temp += session_n[i];
            }
            session_n = temp;
            
            temp = "";
            for (int i = 0; i < session_num.size(); i++)
            {
                if(session_num[i] != ' ')
                    temp += session_num[i];
            }
            session_num = temp;
            
            temp = "";
            for (int i = 0; i < mem_str.size(); i++)
            {
                if(mem_str[i] != ' ' && mem_str[i] != 'K' && mem_str[i] != ',')
                    temp += mem_str[i];
            }
            mem_str = temp;
            mem = stoi(mem_str);
        }

        friend bool operator< (Proccess& a, Proccess& b)
        {
            if(a.name < b.name && a.sort_id == 0 && b.sort_id == 0)
                return true;
            else if(a.pid > b.pid && a.sort_id == 1 && b.sort_id == 1)
                return true;
            else if(a.mem > b.mem && a.sort_id == 2 && b.sort_id == 2)
                return true;
                
            if(a.name > b.name && a.sort_id == 0 && b.sort_id == 0)
                return false;
            else if(a.pid < b.pid && a.sort_id == 1 && b.sort_id == 1)
                return false;
            else if(a.mem < b.mem && a.sort_id == 2 && b.sort_id == 2)
                return false;
            
            
        }

        friend ofstream &operator<< (ofstream& out, Proccess& a);


};

ofstream &operator<< (ofstream& out, Proccess& a)
{

    out << a.name;

    for (int z = 0; z < (40-(a.name.size())-(a.pid_str.size())); z++)
    {
        out << " ";
    }
     
    out << a.pid;

    out << "   ";

    out << a.session_n;

    for (int z = 0; z < 25-(a.session_n.size())-(a.session_num.size()); z++)
    {
        out << " ";
    }
    
    out << a.session_num;

    //out << " ";
    
    for (int z = 0; z < 10-a.mem_str.size(); z++)
    {
        out << " ";
    }
    
    out << a.mem;
    out << " KB" << endl;

    return out;
}

class Proccess_list
{
    protected:
        vector<Proccess> proccesses;

    public:

        Proccess_list(string file, int srt_l)
        {

            ifstream in(file + ".txt");
            string s;

            getline(in, s);
            getline(in, s);
            getline(in, s);

            while(getline(in, s))
            {
                Proccess x(s, srt_l);
                proccesses.push_back(x);
            }

            sort(proccesses.begin(), proccesses.end());

        }

        friend ofstream &operator<< (ofstream& out, Proccess_list& a);

};

ofstream &operator<< (ofstream& out2, Proccess_list& a)
{
    out2 << endl;
    out2 << "Image Name                           PID   Session Name     Session#    Mem Usage\n";
    out2 << "===================      ===============   ==============  ==========  ==========\n";

    for (int i = 0; i < a.proccesses.size(); i++)
    {
        out2 << a.proccesses[i];
    }

    return out2;
    
}


int main()
{
    int order = 0;
    cin >> order;

    while(true)
    {
        _sleep(500);

        system("cls");
        system("tasklist > tasks.txt");

        ofstream out_file;

        out_file.open("output.txt");

        out_file.clear();

        if(order == 0)
        {
            Proccess_list tasks("tasks", order);
            out_file << tasks;
        }
        else if(order == 1)
        {
            Proccess_list tasks("tasks", order);
            out_file << tasks;
        }
        else if(order == 2)
        {
            Proccess_list tasks("tasks", order);
            out_file << tasks;
        }

    }
}