// #include <QCoreApplication>

// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);

//     return a.exec();
// }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <gmpxx.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void writeVectorToFile(const std::vector<mpz_class>& vec, const std::string& filename) {
    FILE* outFile = fopen(filename.c_str(), "wb");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
      //  return;
    }

    for (const auto& num : vec) {
        mpz_out_raw(outFile, num.get_mpz_t());
    }

    fclose(outFile);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<mpz_class> readVectorFromFile(const std::string& filename) {
    std::vector<mpz_class> vec;
    FILE* inFile = fopen(filename.c_str(), "rb");
    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
      //  return vec;
    }

    while (!feof(inFile)) {
        mpz_class num;
        if (mpz_inp_raw(num.get_mpz_t(), inFile) == 0) {
            break; // EOF or error
        }
        vec.push_back(num);
    }

    fclose(inFile);
    return vec;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool vectorsAreEqual(const std::vector<mpz_class>& vec1, const std::vector<mpz_class>& vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //  mpq_class original("1731181/1762217");
     mpz_class original("17311811762217");
    original *= original; original *= original; original *= original;
    original *= original; original *= original; original *= original; // make it a little more interesting...
    original=-original;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // std::vector<mpz_class> vec = {123456789_mpz, 987654321_mpz, 112233445566778899_mpz};
    mpz_class x;
    //  mpz_t
  //  mpz_init( x) =123456789000000//;
  //  *123456789000000*123456789000000*123456789000000;
    std::vector<mpz_class> vec = {original, 987654321, 112233445566778899};
    std::string filename = "/home/viktor/my_projects_qt_2/serialize_vector_GMP/vector_data.bin";

    // Запись вектора в файл
    writeVectorToFile(vec, filename);

    // Чтение вектора из файла
    std::vector<mpz_class> readVec = readVectorFromFile(filename);

    // Проверка равенства векторов
    if (vectorsAreEqual(vec, readVec)) {
        std::cout << "Vectors are equal." << std::endl;
    } else {
        std::cout << "Vectors are not equal." << std::endl;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << vec.at(0) << "\n";
    std::cout << readVec.at(0) << "\n";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return a.exec();
}
