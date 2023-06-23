#include <iostream>
#include <string>

using namespace std;

enum NetworkState
{
    Network_Open,
    Network_Close,
    Network_Connect,
};

class NetworkProcessor
{
    NetworkState state;

public:
    /** 根据状态不同行为变化，同时还会改变状态 */
    void operation1() {
        if (state == Network_Open) {
            // operation1 for Network_Open
            state = Network_Close;
        } else if (state == Network_Close) {
            // operation1 for Network_Close
            state = Network_Connect;
        } else if (state == Network_Connect) {
            // operation1 for Network_Connect
            state = Network_Open;
        }
    }

    void operation2() {
        if (state == Network_Open) {
            // operation2 for Network_Open
            state = Network_Connect;
        } else if (state == Network_Close) {
            // operation2 for Network_Close
            state = Network_Open;
        } else if (state == Network_Connect) {
            // operation2 for Network_Connect
            state = Network_Close;
        }
    }
};
