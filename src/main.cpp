#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Display command line utility usage instructions
void display_help(const string& binary_name) {
    cout << "Usage: " << binary_name << " <L> <R> <TargetThreshold>\n";
    cout << "Arguments:\n";
    cout << "  <L>               : Left boundary for Prefix Sum query (0-indexed, 0 to 7)\n";
    cout << "  <R>               : Right boundary for Prefix Sum query (0-indexed, L to 7)\n";
    cout << "  <TargetThreshold> : Target sum for Two-Pointer search verification\n";
    cout << "Example:\n";
    cout << "  " << binary_name << " 2 5 33\n";
}

int main(int argc, char* argv[]) {
    // Fast I/O Boot
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Guard Clause: Validate system parameters. Expecting exactly 4 elements (binary path + 3 arguments)
    if (argc < 4) {
        cout << "[ERROR] Insufficient execution parameters provided.\n\n";
        display_help(argv[0]);
        return 1;
    }

    // Parse command line inputs safely
    int user_L = stoi(argv[1]);
    int user_R = stoi(argv[2]);
    int target_threshold = stoi(argv[3]);

    // System dataset array bounds
    vector<int> data_stream = {10, 20, 5, 15, 30, 40, 12, 18};
    int n = data_stream.size();

    // Input Validation Guard
    if (user_L < 0 || user_R >= n || user_L > user_R) {
        cout << "[ERROR] Invalid Range bounds requested. Max index is " << n - 1 << ".\n";
        return 1;
    }

    cout << "=======================================================\n";
    cout << "   Dynamic Static-Range Analytics Engine Active        \n";
    cout << "=======================================================\n";

    // ---------------------------------------------------------
    // CORE 1: PREFIX SUM LAYER - Dynamic Query Execution
    // ---------------------------------------------------------
    vector<long long> prefix_sums(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_sums[i + 1] = prefix_sums[i] + data_stream[i];
    }

    // Evaluate user requested range in constant O(1) time
    long long query_result = prefix_sums[user_R + 1] - prefix_sums[user_L];

    // ---------------------------------------------------------
    // CORE 2: TWO-POINTER LAYER - Dynamic Bounding Lookups
    // ---------------------------------------------------------
    vector<int> sorted_workspace = data_stream;
    sort(sorted_workspace.begin(), sorted_workspace.end());

    int left = 0;
    int right = n - 1;
    bool match_found = false;
    int element_a = 0, element_b = 0;

    while (left < right) {
        int current_sum = sorted_workspace[left] + sorted_workspace[right];
        if (current_sum == target_threshold) {
            match_found = true;
            element_a = sorted_workspace[left];
            element_b = sorted_workspace[right];
            break;
        } else if (current_sum < target_threshold) {
            left++;
        } else {
            right--;
        }
    }

    // ---------------------------------------------------------
    // DISPLAY ENGINE REPORT
    // ---------------------------------------------------------
    cout << "-------------------------------------------------------\n";
    cout << " PREFIX SUM ENGINE BOUNDS (Constant Time O(1))\n";
    cout << "-------------------------------------------------------\n";
    cout << " Dynamic Range Query [" << user_L << " to " << user_R << "] | Accumulated Metric: " << query_result << "\n";
    
    cout << "\n-------------------------------------------------------\n";
    cout << " TWO-POINTER BOUNDS SEARCH (Linear Time O(N))\n";
    cout << "-------------------------------------------------------\n";
    if (match_found) {
        cout << " Target Threshold [" << target_threshold << "] Resolved Matrix Pair: " << element_a << " + " << element_b << " = " << target_threshold << "\n";
    } else {
        cout << " Target Threshold [" << target_threshold << "] could not be resolved in the workspace bounds.\n";
    }
    cout << "-------------------------------------------------------\n";

    return 0;
}