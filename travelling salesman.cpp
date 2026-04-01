#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 4   // Number of cities

// Function to find minimum cost
int tsp(int graph[V][V], bool visited[], int currPos, int n, int count, int cost, int *ans) {
    
    // If all cities are visited and return to starting point
    if (count == n && graph[currPos][0]) {
        if (cost + graph[currPos][0] < *ans) {
            *ans = cost + graph[currPos][0];
        }
        return *ans;
    }

    // Try all cities
    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[currPos][i]) {
            
            visited[i] = true;

            tsp(graph, visited, i, n, count + 1, cost + graph[currPos][i], ans);

            visited[i] = false; // backtrack
        }
    }

    return *ans;
}

int main() {
    int graph[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[0] = true; // start from city 0

    int ans = INT_MAX;

    tsp(graph, visited, 0, V, 1, 0, &ans);

    printf("Minimum travelling cost: %d\n", ans);

    return 0;
}