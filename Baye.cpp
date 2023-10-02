#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Data
{
    int customer_id = 0;
    int credit_score = 0;
    string country;
    bool gender; // 0:男 1:女
    int age;
    int tenure;
    float balance;
    int products_number;
    int credit_card;   //好像只有0,1
    int active_member; //好像只有0,1
    float estimated_salary;
    bool answer; // answer = churn
};
struct fixed_Data
{
    int customer_id = 0;
    int credit_score = 0;
    int country;
    bool gender; // 0:男 1:女
    int age;
    int tenure;
    int balance;
    int products_number;
    int credit_card;   //好像只有0,1
    int active_member; //好像只有0,1
    int estimated_salary;
    bool answer; // answer = churn
};
ostream &operator<<(ostream &os, const Data &dt)
{
    os << "customer_id = " << dt.customer_id << endl
       << "credit_score = " << dt.credit_score << endl
       << "country = " << dt.country << endl
       << "gender = " << dt.gender << endl
       << "age = " << dt.age << endl
       << "tenure = " << dt.tenure << endl
       << fixed << setprecision(2) << "balance = " << dt.balance << endl
       << "products_number = " << dt.products_number << endl
       << "credit_card = " << dt.credit_card << endl
       << "active_member = " << dt.active_member << endl
       << fixed << setprecision(2) << "estimated_salary = " << dt.estimated_salary << endl
       << "answer = " << dt.answer << endl;
    return os;
}
ostream &operator<<(ostream &os, const fixed_Data &dt)
{
    os << "customer_id = " << dt.customer_id << endl
       << "credit_score = " << dt.credit_score << endl
       << "country = " << dt.country << endl
       << "gender = " << dt.gender << endl
       << "age = " << dt.age << endl
       << "tenure = " << dt.tenure << endl
       << "balance = " << dt.balance << endl
       << "products_number = " << dt.products_number << endl
       << "credit_card = " << dt.credit_card << endl
       << "active_member = " << dt.active_member << endl
       << "estimated_salary = " << dt.estimated_salary << endl
       << "answer = " << dt.answer << endl;
    return os;
}
void find_max_min(bool isMax, Data tar[], int n)
{

    if (isMax)
    {
        double score = 0, age = 0, tenure = 0, balance = 0, products = 0, estimated = 0;
        for (int i = 0; i < n; i++)
        {
            if (score < tar[i].credit_score)
                score = tar[i].credit_score;
            else if (age < tar[i].age)
                age = tar[i].age;
            else if (tenure < tar[i].tenure)
                tenure = tar[i].tenure;
            else if (balance < tar[i].balance)
                balance = tar[i].balance;
            else if (products < tar[i].products_number)
                products = tar[i].products_number;
            else if (estimated < tar[i].estimated_salary)
                estimated = tar[i].estimated_salary;
        }
        cout << score << " " << age << " " << tenure << " " << balance << " " << products << " " << estimated << endl;
    }
    else
    {
        double score = INT_MAX, age = INT_MAX, tenure = INT_MAX, balance = INT_MAX, products = INT_MAX, estimated = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (score > tar[i].credit_score)
                score = tar[i].credit_score;
            else if (age > tar[i].age)
                age = tar[i].age;
            else if (tenure > tar[i].tenure)
                tenure = tar[i].tenure;
            else if (balance > tar[i].balance)
                balance = tar[i].balance;
            else if (products > tar[i].products_number)
                products = tar[i].products_number;
            else if (estimated > tar[i].estimated_salary)
                estimated = tar[i].estimated_salary;
        }
        cout << score << " " << age << " " << tenure << " " << balance << " " << products << " " << estimated << endl;
    }
}
double byes(int n, fixed_Data tar[], double test_begin, double test_end)
{
    cout << "////////////////////////////////" << endl;
    cout << "訓練範圍 : " << test_begin << "~" << test_end << endl;
    double train = n - test_end + test_begin;
    // churn = 1
    int c_score[4] = {0}, c_country[3] = {0}, c_gender[2] = {0}, c_age[4] = {0}, c_tenure[11] = {0};
    int c_balance[2] = {0}, c_products[4] = {0}, c_card[2] = {0}, c_active[2], c_estimated[4], c = 0;
    // churn = 0
    int uc_score[4] = {0}, uc_country[3] = {0}, uc_gender[2] = {0}, uc_age[4] = {0}, uc_tenure[11] = {0};
    int uc_balance[2] = {0}, uc_products[4] = {0}, uc_card[2] = {0}, uc_active[2] = {0}, uc_estimated[4] = {0}, uc = 0;

    for (int i = 0; i < n; i++)
    {
        if (i > test_begin && i < test_end)
        {
            continue;
        }
        if (tar[i].answer == 1)
        {
            c_score[tar[i].credit_score]++;
            c_country[tar[i].country]++;
            c_gender[tar[i].gender]++;
            c_age[tar[i].age]++;
            c_tenure[tar[i].tenure]++;
            c_balance[tar[i].balance]++;
            c_products[tar[i].products_number - 1]++;
            c_card[tar[i].credit_card]++;
            c_active[tar[i].active_member]++;
            c_estimated[tar[i].estimated_salary]++;
            c++;
        }
        else
        {
            uc_score[tar[i].credit_score]++;
            uc_country[tar[i].country]++;
            uc_gender[tar[i].gender]++;
            uc_age[tar[i].age]++;
            uc_tenure[tar[i].tenure]++;
            uc_balance[tar[i].balance]++;
            uc_products[tar[i].products_number - 1]++;
            uc_card[tar[i].credit_card]++;
            uc_active[tar[i].active_member]++;
            uc_estimated[tar[i].estimated_salary]++;
            uc++;
        }
    }
    /*
        cout << c_score[0] << endl;
        cout << c_score[1] << endl;
        cout << c_score[2] << endl;
        cout << c_score[3] << endl;
        cout << uc_score[0] << endl;
        cout << uc_score[1] << endl;
        cout << uc_score[2] << endl;
        cout << uc_score[3] << endl;
        cout << "total score sum = " << c_score[0] + c_score[1] + c_score[2] + c_score[3] + uc_score[0] + uc_score[1] + uc_score[2] + uc_score[3] << endl;*/
    //計算機率
    // cout << "c = " << c << endl
    //     << "uc = " << uc << endl;
    float pc_score[4] = {0}, pc_country[3] = {0}, pc_gender[2] = {0}, pc_age[4] = {0}, pc_tenure[11] = {0};
    float pc_balance[2] = {0}, pc_products[4] = {0}, pc_card[2] = {0}, pc_active[2] = {0}, pc_estimated[4] = {0}, pc = 0;
    // churn = 0
    float puc_score[4] = {0}, puc_country[3] = {0}, puc_gender[2] = {0}, puc_age[4] = {0}, puc_tenure[11] = {0};
    float puc_balance[2] = {0}, puc_products[4] = {0}, puc_card[2] = {0}, puc_active[2] = {0}, puc_estimated[4] = {0}, puc = 0;
    for (int i = 0; i < 4; i++)
    {
        pc_score[i] = c_score[i] / train;
        puc_score[i] = uc_score[i] / train;
        pc_products[i] = c_products[i] / train;
        puc_products[i] = uc_products[i] / train;
        pc_estimated[i] = c_estimated[i] / train;
        puc_estimated[i] = uc_estimated[i] / train;
        pc_age[i] = c_age[i] / train;
        puc_age[i] = uc_age[i] / train;
    }
    for (int i = 0; i < 3; i++)
    {
        pc_country[i] = c_country[i] / train;
        puc_country[i] = uc_country[i] / train;
    }
    for (int i = 0; i < 2; i++)
    {
        pc_gender[i] = c_gender[i] / train;
        puc_gender[i] = uc_gender[i] / train;
        pc_balance[i] = c_balance[i] / train;
        puc_balance[i] = uc_balance[i] / train;
        pc_card[i] = c_card[i] / train;
        puc_card[i] = uc_card[i] / train;
        pc_active[i] = c_active[i] / train;
        puc_active[i] = uc_active[i] / train;
    }
    for (int i = 0; i < 11; i++)
    {
        pc_tenure[i] = c_tenure[i] / train;
        puc_tenure[i] = uc_tenure[i] / train;
    }
    pc = c / train;
    puc = uc / train;

    // cout << "pc = " << fixed << setprecision(2) << pc << endl
    //      << "puc = " << fixed << setprecision(2) << puc << endl;
    // cout << "p_card = " << pc_card[0] + pc_card[1] + puc_card[0] + puc_card[1] << endl;
    int table[2][2] = {0};
    int real[2] = {0}, predict[2] = {0};
    double predict_pc = 0, predict_puc = 0;
    for (int i = test_begin; i < test_end; i++)
    {

        // cout << "predice = " << endl;
        // full
        predict_pc = pc * pc_score[tar[i].credit_score] * pc_country[tar[i].country] * pc_gender[tar[i].gender] * pc_age[tar[i].age] * pc_tenure[tar[i].tenure] * pc_balance[tar[i].balance] * pc_products[tar[i].products_number] * pc_card[tar[i].credit_card] * pc_active[tar[i].active_member] * pc_estimated[tar[i].estimated_salary];
        predict_puc = puc * puc_score[tar[i].credit_score] * puc_country[tar[i].country] * puc_gender[tar[i].gender] * puc_age[tar[i].age] * puc_tenure[tar[i].tenure] * puc_balance[tar[i].balance] * puc_products[tar[i].products_number] * puc_card[tar[i].credit_card] * puc_active[tar[i].active_member] * puc_estimated[tar[i].estimated_salary];
        // no estimated
        // predict_pc = pc * pc_score[tar[i].credit_score] * pc_country[tar[i].country] * pc_gender[tar[i].gender] * pc_age[tar[i].age] * pc_tenure[tar[i].tenure] * pc_balance[tar[i].balance] * pc_products[tar[i].products_number] * pc_card[tar[i].credit_card] * pc_active[tar[i].active_member] * 1;
        // predict_puc = puc * puc_score[tar[i].credit_score] * puc_country[tar[i].country] * puc_gender[tar[i].gender] * puc_age[tar[i].age] * puc_tenure[tar[i].tenure] * puc_balance[tar[i].balance] * puc_products[tar[i].products_number] * puc_card[tar[i].credit_card] * puc_active[tar[i].active_member] * 1;
        // no balance
        // predict_pc = pc * pc_score[tar[i].credit_score] * pc_country[tar[i].country] * pc_gender[tar[i].gender] * pc_age[tar[i].age] * pc_tenure[tar[i].tenure] * 1 * pc_products[tar[i].products_number] * pc_card[tar[i].credit_card] * pc_active[tar[i].active_member] * pc_estimated[tar[i].estimated_salary];
        // predict_puc = puc * puc_score[tar[i].credit_score] * puc_country[tar[i].country] * puc_gender[tar[i].gender] * puc_age[tar[i].age] * puc_tenure[tar[i].tenure] * 1 * puc_products[tar[i].products_number] * puc_card[tar[i].credit_card] * puc_active[tar[i].active_member] * puc_estimated[tar[i].estimated_salary];
        // no balance no estimated
        // predict_pc = pc * pc_score[tar[i].credit_score] * pc_country[tar[i].country] * pc_gender[tar[i].gender] * pc_age[tar[i].age] * pc_tenure[tar[i].tenure] * 1 * pc_products[tar[i].products_number] * pc_card[tar[i].credit_card] * pc_active[tar[i].active_member] * 1;
        // predict_puc = puc * puc_score[tar[i].credit_score] * puc_country[tar[i].country] * puc_gender[tar[i].gender] * puc_age[tar[i].age] * puc_tenure[tar[i].tenure] * 1 * puc_products[tar[i].products_number] * puc_card[tar[i].credit_card] * puc_active[tar[i].active_member] * 1;
        // cout << fixed << setprecision(15) << predict_pc + predict_puc << endl;
        if (predict_pc >= predict_puc)
        {
            if (tar[i].answer == 1)
                table[0][0]++; //猜對 是YES
            else
                table[0][1]++; //猜錯 是NO
        }
        else
        {
            if (tar[i].answer == 0)
                table[1][1]++; //猜對 是NO
            else
                table[1][0]++; //猜錯 是1
        }
    }

    // cout << "table[0]  = " << table[0][0] << "  " << table[0][1] << endl;
    // cout << "table[1]  = " << table[1][0] << "  " << table[1][1] << endl;
    real[0] = table[0][0] + table[1][0];
    real[1] = table[0][1] + table[1][1];
    predict[0] = table[0][0] + table[0][1];
    predict[1] = table[1][0] + table[1][1];
    // cout << "real = " << real[0] << " || " << real[1] << endl;
    // cout << "predict = " << predict[0] << " || " << predict[1] << endl;
    //  cout << "total1 = " << real[0] + real[1] << endl;
    //  cout << "total2 = " << predict[0] + predict[1] << endl;
    double Accur = (table[0][0] + table[1][1]) / (n - train);
    double error_rate = (table[1][0] + table[0][1]) / (n - train);
    cout << "Accuracy = " << fixed << setprecision(2) << Accur << endl;
    cout << "error rate = " << fixed << setprecision(2) << error_rate << endl;
    return Accur;
}
int main()
{
    double tmp_dou;
    Data customer[10000];
    fixed_Data ans[10000];
    int cut_sum = 0;
    int tmp_int;
    ifstream file;
    file.open("Bank_Customer.csv");
    // file.open("testt.csv");
    string line;
    string tmp[5][5];
    char ch = '"';
    string::iterator it;
    int sum = 0;
    int now_data;
    string coun[100];
    int coun_sum = 0;
    bool coun_new = true;
    while (getline(file, line, '\n')) //讀檔讀到跳行字元
    {
        if (sum == 0)
        {
            sum++;
            continue;
        }
        sum++;
        istringstream templine(line); // string 轉換成 stream
        string data;
        now_data = 0;
        while (getline(templine, data, ',')) //讀檔讀到逗號
        {
            for (it = data.begin(); it < data.end(); it++)
            {
                if (*it == ch)
                {
                    data.erase(it);
                    it--;
                }
            }
            // tmp_int = stoi(data);
            // cout << tmp_int << " ";
            now_data++;
            if (now_data == 1)
            {
                customer[cut_sum].customer_id = stoi(data);
                // cout << customer[0].customer_id << "**";
                continue;
            }

            else if (now_data == 2)
            {
                customer[cut_sum].credit_score = stoi(data);
                continue;
            }

            else if (now_data == 3)
            {
                coun_new = true;
                customer[cut_sum].country = data;
                if (coun_new)
                {
                    for (int i = 0; i < coun_sum; i++)
                    {
                        if (coun[i] == data)
                            coun_new = false;
                    }
                    if (coun_new)
                    {
                        coun[coun_sum] = data;
                        // cout << data << endl;
                        coun_sum++;
                    }
                }
                continue;
            }
            else if (now_data == 4)
            {
                if (data == "Female")
                    customer[cut_sum].gender = 1;
                else if (data == "Male")
                    customer[cut_sum].gender = 0;
                continue;
            }
            else if (now_data == 5)
            {
                customer[cut_sum].age = stoi(data);
                continue;
            }
            else if (now_data == 6)
            {
                customer[cut_sum].tenure = stoi(data);
                continue;
            }
            else if (now_data == 7)
            {
                customer[cut_sum].balance = stof(data);
                continue;
            }
            else if (now_data == 8)
            {
                customer[cut_sum].products_number = stoi(data);
                continue;
            }
            else if (now_data == 9)
            {
                customer[cut_sum].credit_card = stoi(data);
                continue;
            }
            else if (now_data == 10)
            {
                customer[cut_sum].active_member = stoi(data);
                continue;
            }
            else if (now_data == 11)
            {
                customer[cut_sum].estimated_salary = stof(data);
                continue;
            }
            else if (now_data == 12)
            {
                customer[cut_sum].answer = stoi(data);
                continue;
            }
        }
        cut_sum++;
    }
    // cout << customer[0];
    // find_max_min(1, customer, 10000);
    // find_max_min(0, customer, 10000);
    for (int i = 0; i < 10000; i++)
    {
        // id
        ans[i].customer_id = customer[i].customer_id;
        // credit_score
        if (customer[i].credit_score <= 475)
            ans[i].credit_score = 0;
        else if (customer[i].credit_score <= 600)
            ans[i].credit_score = 1;
        else if (customer[i].credit_score <= 725)
            ans[i].credit_score = 2;
        else if (customer[i].credit_score <= 850)
            ans[i].credit_score = 3;
        // country
        if (customer[i].country == "France")
            ans[i].country = 0;
        else if (customer[i].country == "Spain")
            ans[i].country = 1;
        else if (customer[i].country == "Germany")
            ans[i].country = 2;
        // gender
        ans[i].gender = customer[i].gender;
        /*
        if (customer[i].gender <= 3)
            ans[i].gender = 0;
        else if (customer[i].gender <= 7)
            ans[i].gender = 1;
        else if (customer[i].gender > 7)
            ans[i].gender = 2;
            */
        // age
        if (customer[i].age <= 36)
            ans[i].age = 0;
        else if (customer[i].age <= 54)
            ans[i].age = 1;
        else if (customer[i].age <= 72)
            ans[i].age = 2;
        else if (customer[i].age > 72)
            ans[i].age = 3;
        // tenure
        ans[i].tenure = customer[i].tenure;
        // blance
        if (customer[i].balance <= 10)
            ans[i].balance = 0;
        else if (customer[i].balance > 10)
            ans[i].balance = 1;
        // products_num
        ans[i].products_number = customer[i].products_number;
        // credit_card
        ans[i].credit_card = customer[i].credit_card;
        // active
        ans[i].active_member = customer[i].active_member;
        // estimatied
        if (customer[i].estimated_salary <= 24000)
            ans[i].estimated_salary = 0;
        else if (customer[i].estimated_salary <= 48000)
            ans[i].estimated_salary = 1;
        else if (customer[i].estimated_salary <= 100000)
            ans[i].estimated_salary = 2;
        else if (customer[i].estimated_salary > 100000)
            ans[i].estimated_salary = 3;
        // churn
        ans[i].answer = customer[i].answer;
    }
    // out << ans[181];
    double acc[10];
    int tmp_acc;
    double total_acc = 0;
    double ave_acc;
    // acc[0] = byes(10000, ans, 0, 1000);
    for (int i = 0; i < 10; i++)
    {
        tmp_acc = i * 1000;
        acc[i] = byes(10000, ans, tmp_acc, tmp_acc + 1000);
        // cout << "acc[" << i << "] = " << acc[i] << endl;
        total_acc += acc[i];
    }
    ave_acc = total_acc / 10;
    // cout << "ave acc = " << fixed << setprecision(4) << total_acc << endl;
    cout << "////////////" << endl;
    cout << "平均精準度 = " << fixed << setprecision(4) << ave_acc << endl;
    file.close();
}
// cout << score << " " << age << " " << tenure << " " << balance << " " << products << " " << estimated << endl;
/*
    score   age     tenure  balance     products    estimated
MAX 850.00  92.00   10.00   250898.09   4.00        199992.48
MIN 350.00  18.00   0.00    0.00        1.00        11.58

    350~475 18~36           0           1           <24000
    475~600 37~54           1           2           <48000
    600~725 55~72                       3           <100000
    725~850 73~92                       4           >100000
    0~3     0~4     0~11    0~1         1~4         0~3
*/
