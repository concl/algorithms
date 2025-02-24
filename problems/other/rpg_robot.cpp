
#include <bits/stdc++.h>

using namespace std;


class RPGRobot {
public:
    vector<string> where(vector<string> map, string movements) {

        // First, let's find the size of the map.
        // Since each gamespace is surrounded by walls, we can divide the size of the map by 2 to find the number of rows and columns
        int rows = map.size() / 2, cols = map[0].size() / 2;
        int map_rows = map.size(), map_cols = map[0].size();

        // Now, let's tokenize the movements.
        // Each movement is represented in the format which specifies the possible directions, and which direction was chosen.
        // At the last position, the directions are specified, but not the chosen direction.
        vector<pair<string, string>> tokens;

        bool parsing_move = false;
        string directions = "", move = "";
        for (char c : movements) {
            if (c == ',') {
                parsing_move = true;
                continue;
            } else if (c == ' ') {
                parsing_move = false;
                tokens.push_back({directions, move});
                directions = "";
                move = "";
                continue;
            }

            if (parsing_move) {
                move += c;
            } else {
                directions += c;
            }
        }
        tokens.push_back({directions, move});

        // Now, let's consider each gamespace to see if it is a valid starting point.
        vector<string> res;
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {

                bool valid = true;
                
                // Keep track of the current position
                int row = i;
                int col = j;

                for (pair<string, string> token : tokens) {
                    
                    string directions = token.first;
                    string move = token.second;
                    

                    // Check if the directions are valid
                    string cardinals = "NSEW";
                    vector<pair<int, int>> direc = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
                    for (int i = 0; i < 4; i++) {
                        int nr = 2 * row + 1 + direc[i].first;
                        int nc = 2 * col + 1 + direc[i].second;

                        if (nr >= 0 && nr < map_rows && nc >= 0 && nc < map_cols) {
                            
                            if ((map[nr][nc] == '-' || map[nr][nc] == '|') && (directions.find(cardinals[i]) != string::npos)) {
                                valid = false;
                                break;
                            } else if (map[nr][nc] == ' ' && directions.find(cardinals[i]) == string::npos) {
                                valid = false;
                                break;
                            }
                        }
                    }

                    // Move the robot
                    if (move == "N") {
                        row--;
                    } else if (move == "S") {
                        row++;
                    } else if (move == "E") {
                        col++;
                    } else if (move == "W") {
                        col--;
                    }

                    if (!valid) break;
                }
                
                // If the position is valid, add it to the result
                if (valid) {
                    res.push_back(to_string(j * 2 + 1) + "," + to_string(i * 2 + 1));
                }

            }
        }

        return res;
    }
};




int main() {

    

    return 0;
}