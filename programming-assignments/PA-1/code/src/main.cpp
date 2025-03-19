#include "./../include/wrapper/AppWrapper.hpp"

int main(int argc, char** argv) {
    AppWrapper& app = AppWrapper::GetInstance();
    app.Run(argc, argv);
    return 0;
}