
#include "stream/stream_handler.hpp"
#include <stdexcept>
#include <iostream>

int main(){
	webcam_test::StreamHandler* sh = new webcam_test::StreamHandler();
	try{
		sh->run();
	}catch(const std::exception& e){
		std::cerr << e.what() << '\n';
	}
    delete sh;
    return 0;
}