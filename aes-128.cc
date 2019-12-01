#include <fstream>
#include <string>
#include <sstream>
#include "encrypt.h"

int main ()
{
    std::string f_in = "11.txt";

    FileReader file_in = FileReader (f_in,true);
    HexType inh = file_in.GetAscii().GetHex();

    int count = 0;
    do
    {
        HexType key = HexType (GetRandomKey());
        KeyType kt = KeyType (key);
        std::vector<HexType> ks = kt.GetKeySchedule();

        EncryptECB tmp;
        HexType ct = tmp.EncryptInputECB (inh,ks);
        std::cout << "\n  is the output ECB = " << ct.isECB() << std::endl;


        HexType hiv = HexType (GetRandomIV(32));

        EncryptCBC tmp_c;
        HexType ct_cbc = tmp_c.EncryptInputCBC(inh,hiv,ks);

        std::cout << "\n is the output ECB = " << ct_cbc.isECB() << std::endl;

        count++;
    }while (count <100);
}
