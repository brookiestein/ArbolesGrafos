#include <iostream>
#include <print>
#include <queue>
#include <vector>

class ComputerNetwork
{
    bool isValidComputer(int computer) const
    {
        return computer >= 0 &&
               computer < static_cast<int>(m_adjacencyList.size());
    }

public:
    explicit ComputerNetwork(int numberOfComputers)
        : m_adjacencyList(numberOfComputers)
    {
    }

    void addConnection(int computerA, int computerB)
    {
        if (!isValidComputer(computerA) || !isValidComputer(computerB)) {
            std::println(stderr, "Conexión invalida.");
            return;
        }

        m_adjacencyList[computerA].push_back(computerB);
        m_adjacencyList[computerB].push_back(computerA);
    }

    void displayNetwork() const
    {
        std::println("\nLista de adyacencia:");

        for (int computer = 0;
             computer < static_cast<int>(m_adjacencyList.size()); ++computer) {
            std::print("Computadora {}: ", computer);

            for (int neighbor : m_adjacencyList[computer]) {
                std::print("{} ", neighbor);
            }

            std::println();
        }
    }

    void propagateUpdate(int start) const
    {
        if (!isValidComputer(start)) {
            std::println(stderr, "Computadora inicial inválida.");
            return;
        }

        std::vector<bool> visited(m_adjacencyList.size(), false);
        std::queue<int> pending;

        visited[start] = true;
        pending.push(start);

        std::println("\nOrden de propagacion de la actualizacion:");

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();

            std::print("{} ", current);

            for (int neighbor : m_adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    pending.push(neighbor);
                }
            }
        }

        std::println();
    }

    int minimumHops(int origin, int destination) const
    {
        if (!isValidComputer(origin) || !isValidComputer(destination)) {
            return -1;
        }

        std::vector<int> distance(m_adjacencyList.size(), -1);
        std::queue<int> pending;

        distance[origin] = 0;
        pending.push(origin);

        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();

            if (current == destination) {
                return distance[current];
            }

            for (int neighbor : m_adjacencyList[current]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[current] + 1;

                    pending.push(neighbor);
                }
            }
        }

        return -1;
    }

private:
    std::vector<std::vector<int>> m_adjacencyList;
};

int main()
{
    int numberOfComputers {};
    int numberOfConnections {};

    std::print("Cantidad de computadoras: ");
    std::cin >> numberOfComputers;

    ComputerNetwork network(numberOfComputers);

    std::print("Cantidad de conexiones: ");
    std::cin >> numberOfConnections;

    std::println("\nIngrese las conexiones.");
    std::println("Ejemplo: 0 1\n");

    for (int i = 0; i < numberOfConnections; ++i) {
        int computerA;
        int computerB;

        std::print("Conexión {}: ", (i + 1));
        std::cin >> computerA >> computerB;

        network.addConnection(computerA, computerB);
    }

    network.displayNetwork();

    int startComputer;

    std::print("\nComputadora donde inicia la actualizacion: ");
    std::cin >> startComputer;

    network.propagateUpdate(startComputer);

    int origin;
    int destination;

    std::print("\nComputadora de origen: ");
    std::cin >> origin;

    std::print("Computadora de destino: ");
    std::cin >> destination;

    int hops = network.minimumHops(origin, destination);

    if (hops == -1) {
        std::println("\nNo existe una ruta entre las computadoras.");
    } else {
        std::println("\nNumero mínimo de saltos entre {} y {}: {}", origin, destination, hops);
    }
}
