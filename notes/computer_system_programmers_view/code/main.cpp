#include "echoserver_process.h"
#include "echoserver_select_basic.h"
#include "echoserver_select.h"
#include "echo_client.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;
using UnknownOptionException = boost::wrapexcept<po::unknown_option>;

static constexpr auto NOT_SPECIFIED_INT = INT_MAX;

int main(int argc, char** argv) {
    po::options_description desc("specify -t.\n"
                                  "    ec:  echoclient\n"
                                  "    es:  echoserver_select\n"
                                  "    esb: echoserver_select_basic\n"
                                  "    ep:  echoserver_process\n"
                              );
    std::string appType;
    std::string host;
    int port = 0;
    desc.add_options()
        ("help", "produce help message")
        ("appType,t", po::value<std::string>(&appType)->default_value(""), "what apps to build")
        ("host,h", po::value<std::string>(&host)->default_value("localhost"), "host")
        ("port,p", po::value<int>(&port)->default_value(33456), "port")
        ;
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    } catch (UnknownOptionException& e) {
        std::cerr << e.what() << "..." << std::endl;
        return 1;
    }
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (appType == "ec") {
        echoclient::run(host, port);
    } else if (appType == "es") {
        echoserver_select::run(port);
    } else if (appType == "esb") {
        echoserver_select_basic::run(port);
    } else if (appType == "ep") {
        echoserver_process::run(port);
    } else {
        std::cerr << "non-specified app\n";
    }
    return 0;
}
