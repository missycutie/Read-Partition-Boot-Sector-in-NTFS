#include "helper.h"
uint64_t convertBytesToInt(const BYTE bytes[], int n) {
    uint64_t res = 0;
    for (int i = n - 1; i >= 0; i--) {
        res = (res << 8) | bytes[i];
    }
    return res;
}

string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

string bitwise_complement(string strbit){
    for (int i = 0; i < strbit.length(); i++){
       strbit[i] = (strbit[i] == '0' ? '1' : '0');
    }
    return strbit;
}

string toHex(unsigned int decnum) {
    string hexnum = "";
    int rem;
    while(decnum != 0)
    {
        rem = decnum % 16;
        if(rem < 10)
            rem = rem + '0';
        else
            rem = rem - 10 + 'A';
        hexnum = (char)rem + hexnum;
        decnum = decnum / 16;
    }
    return hexnum.size() >= 2 ? hexnum : hexnum.size() == 1 ? "0" + hexnum : "00";
}
