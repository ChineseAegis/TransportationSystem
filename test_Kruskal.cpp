#include"WUSGraphClient.hpp"
#include "catch.hpp"
//#include "WUSGraph.hpp"
#include "Forest.hpp"

TEST_CASE("Kruskal functionality tests", "[Kruskal]") {
    WUSGraph<std::string, int> g;
    // 构建具有已知最小生成森林的测试图
    // 例如：
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
     g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 3);
     g.addEdge("B", "C", 2);
     g.addEdge("C", "D", 4);
    // ...

        WUSGraphClient<std::string, int> client;
        Forest<std::string, int> msf;

        client.Kruskal(g, msf);
        msf.printWholeForest();
        
    
}
