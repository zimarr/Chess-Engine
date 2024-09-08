#include <iostream>
#include <stack>
#include "player.h"
#include "move.h"

struct TestMove {
    TestMove (Move m, Player* p) {
        move = m;
        player = p;
    }

    Move move;
    Player* player;
};

using namespace std;

void simulate(Player* player, int num_steps, std::vector<Move>& botMoves) {
    // std::stack<TestMove> moves_made;
    // std::stack<Move> enemy_moves_made;
    
    // int step = num_steps;

    // while (step > 0) {
    //     for (Piece* piece : player->pieces) {
    //         std::vector<Move> moves = piece->getMoves(player);
    //         for (Move& move : moves) {
    //             if (step == num_steps) {
    //                 botMoves.push_back(move);
    //             }
                
    //             move.make(player);
    //             moves_made.push(TestMove(move, player));

    //             for (Piece* enemy_piece : player->opponent->pieces) {
    //                 std::vector<Move> enemy_moves = enemy_piece->getMoves(player->opponent);
    //                 for (Move& enemy_move : enemy_moves) {
    //                     enemy_move.make(player->opponent);
    //                     moves_made.push(TestMove(enemy_move, player->opponent));

    //                     if (step == 1) {    // evaluate
    //                         // cout << player->points << endl;
    //                         moves_made.top().move.undo(moves_made.top().player);
    //                         moves_made.pop();
    //                     }

                        
    //                 }
    //             }

    //             if (step == 1) {
    //                 moves_made.top().move.undo(moves_made.top().player);
    //                 moves_made.pop();
    //             }    
    //                 // move.undo(player);

    //         }
    //     }

    //     step--;
    // }

    // while (!moves_made.empty()) {
    //     TestMove move_made = moves_made.top();
    //     moves_made.pop();
        
    //     move_made.move.undo(move_made.player);
    // }

    // cout << "GRA" << endl;
    

    // if (num_steps <= 0) {
    //     return;
    // }

    // for (Piece* piece : player->pieces) {
    //     player->makingMove = true;

    //     std::vector<Move> moves = piece->getMoves(player);

    //     player->makingMove = false;

    //     for (Move& move : moves) {
    //         if (num_steps == 1) {
    //             botMoves.push_back(move);
    //         }
            
    //         move.make(player);

    //         for (Piece* enemy_piece : player->opponent->pieces) {
    //             player->opponent->makingMove = true;
                
    //             std::vector<Move> enemy_moves = enemy_piece->getMoves(player->opponent);
                
    //             player->opponent->makingMove = false;

    //             for (Move& enemy_move : enemy_moves) {
    //                 enemy_move.make(player->opponent);
                    
    //                 simulate(player, num_steps - 1, botMoves);

    //                 enemy_move.undo(player->opponent);
    //             }
    //         }

    //         move.undo(player);
    //     }
    // }

}











