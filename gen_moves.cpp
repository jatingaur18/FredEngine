#include <bits/stdc++.h>
#include <iostream>
#include "board.h"
#include "utils.h"
using namespace std;


static inline int lsb_ind(usl bitboard) {
    if (bitboard) {
        return __builtin_ctzll(bitboard);
    }
    else {
        return -1;
    }
}

void chessboard::generate_moves(){
    int source,target;
    usl board;
    usl attack;
    for(int i=P;i<=k;i++){
        board=pisces[i];
        if(!side){
            if(i==P){
                cout<<"--------- Generating Pawn Move --------"<<endl;
                while(board){
                    source=lsb_ind(board);
                    target=source-8;
                    string s=index_to_square(source);
                    if(target >=0 && !getBit(target)){

                        if(target<=h8 ){
                            cout<<s<<index_to_square(target)<<"N promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"B promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"R promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"Q promotion"<<endl;
                        }
                        else{
                            //normal move
                            cout<<s<<index_to_square(target)<<endl;
                            //double move
                            if(source >=a2 && source<=h2 && target-8 >= 0 && !getBit(target-8)){
                                cout<<s<<index_to_square(target-8)<<endl;
                            }
                            // cout<<endl;
                        }
                    }

                    attack= pawn_attacks_table[side][source] & color_bitboards[BLACK];
                    while(attack){
                        target=lsb_ind(attack);
                        if(target<=h8 ){
                            cout<<s<<"x"<<index_to_square(target)<<"N promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"B promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"R promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"Q promotion"<<endl;
                        }
                        else{
                            cout<<s<<"x"<<index_to_square(target)<<endl;
                        }
                    
                        remBit(target,attack);
                    }
                    if(en_passant!=-1){
                        attack= pawn_attacks_table[side][source] & (1ULL<<en_passant);
                        if(attack){
                            cout<<s<<"x"<<index_to_square(en_passant)<<" "<<index_to_square(en_passant+8)<<endl;
                        }
                    }
                    
                    remBit(source,board);
                    
                }
            }
            else if(i==K && !is_sq_attacked(60,BLACK) ){
                cout<<endl;
                cout<<"--------- Generating Castling Move --------"<<endl;

                if(castling & WK ){
                    if( !getBit(61) && !getBit(62)
                        && !is_sq_attacked(61,BLACK) 
                        && !is_sq_attacked(62,BLACK)){
                        cout<<"O-O"<<endl;
                    }
                }
                if(castling & WQ){
                    if( !getBit(57) && !getBit(58) && !getBit(59)
                        && !is_sq_attacked(60,BLACK) 
                        && !is_sq_attacked(59,BLACK) 
                        && !is_sq_attacked(58,BLACK)){
                        cout<<"O-O-O"<<endl;
                    }
                }
            }
        }
        else{
            if(i==p){
                cout<<endl;
                cout<<"--------- Generating Pawn Move --------"<<endl;
                while(board){
                    source=lsb_ind(board);
                    target=source+8;
                    string s=index_to_square(source);
                    if(target >=0 && !getBit(target)){

                        if(target>=a1 ){
                            cout<<s<<index_to_square(target)<<"N promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"B promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"R promotion"<<endl;
                            cout<<s<<index_to_square(target)<<"Q promotion"<<endl;
                        }
                        else{
                            //normal move
                            cout<<s<<index_to_square(target)<<endl;
                            //double move
                            if(source >=a7 && source<=h7 && target+8 >= 0 && !getBit(target+8)){
                                cout<<s<<index_to_square(target+8)<<endl;
                            }
                            // cout<<endl;
                        }
                    }
                    attack= pawn_attacks_table[side][source] & color_bitboards[WHITE];
                    while(attack){
                        target=lsb_ind(attack);
                        if(target<=h8 ){
                            cout<<s<<"x"<<index_to_square(target)<<"N promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"B promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"R promotion"<<endl;
                            cout<<s<<"x"<<index_to_square(target)<<"Q promotion"<<endl;
                        }
                        else{
                            cout<<s<<"x"<<index_to_square(target)<<endl;
                        }
                    
                        remBit(target,attack);
                    }
                    if(en_passant!=-1){
                        attack= pawn_attacks_table[side][source] & (1ULL<<en_passant);
                        if(attack){
                            cout<<s<<"x"<<index_to_square(en_passant)<<" "<<index_to_square(en_passant-8)<<endl;
                        }
                    }
                        // attack&=attack-1;
                    remBit(source,board);
                    // printBoard(board);
                }
            }
            else if(i==k && !is_sq_attacked(4,WHITE)){
                cout<<endl;
                cout<<"--------- Generating Castling Move --------"<<endl;

                if(castling & BK){
                    if( !getBit(5) && !getBit(6)
                        && !is_sq_attacked(5,WHITE) 
                        && !is_sq_attacked(6,WHITE)){
                        cout<<"O-O"<<endl;
                    }
                }
                if(castling & BQ){
                    if( !getBit(1) && !getBit(2) && !getBit(3)
                        && !is_sq_attacked(2,WHITE) 
                        && !is_sq_attacked(3,WHITE)){
                        cout<<"O-O-O"<<endl;
                    }
                }
            }
        }
        if(!side? i==N:i==n){
            cout<<endl;
            cout<<"--------- Generating Knight Move --------"<<endl;

            while(board){
                source=lsb_ind(board);
                attack=knight_attacks_table[source] & (!side? ~color_bitboards[WHITE]: ~color_bitboards[BLACK]);
                string s=index_to_square(source);
                while(attack){
                    target=lsb_ind(attack);
                    if(getBit(target)){
                        cout<<s<<"x"<<index_to_square(target)<<endl;
                    }
                    else{
                        cout<<s<<index_to_square(target)<<endl;
                    }
                    remBit(target,attack);
                }
                remBit(source,board);
            }
        }

        else if(!side? i==B:i==b){
            cout<<endl;
            cout<<"--------- Generating Bishop Move --------"<<endl;

            while(board){
                source=lsb_ind(board);
                attack=bishop_attacks(source,bitboard) & (!side? ~color_bitboards[WHITE]: ~color_bitboards[BLACK]);
                string s=index_to_square(source);
                while(attack){
                    target=lsb_ind(attack);
                    if(getBit(target)){
                        cout<<s<<"x"<<index_to_square(target)<<endl;
                    }
                    else{
                        cout<<s<<index_to_square(target)<<endl;
                    }
                    remBit(target,attack);
                }
                remBit(source,board);
            }
        }
        else if(!side? i==R:i==r){
            cout<<endl;
            cout<<"--------- Generating Rook Move --------"<<endl;

            while(board){
                source=lsb_ind(board);
                attack=rook_attacks(source,bitboard) & (!side? ~color_bitboards[WHITE]: ~color_bitboards[BLACK]);
                string s=index_to_square(source);
                while(attack){
                    target=lsb_ind(attack);
                    if(getBit(target)){
                        cout<<s<<"x"<<index_to_square(target)<<endl;
                    }
                    else{
                        cout<<s<<index_to_square(target)<<endl;
                    }
                    remBit(target,attack);
                }
                remBit(source,board);
            }
        }
        else if(!side? i==Q:i==q){
            cout<<endl;
            cout<<"--------- Generating Queen Move --------"<<endl;

            while(board){
                source=lsb_ind(board);
                attack=queen_attacks(source,bitboard) & (!side? ~color_bitboards[WHITE]: ~color_bitboards[BLACK]);
                string s=index_to_square(source);
                while(attack){
                    target=lsb_ind(attack);
                    if(getBit(target)){
                        cout<<s<<"x"<<index_to_square(target)<<endl;
                    }
                    else{
                        cout<<s<<index_to_square(target)<<endl;
                    }
                    remBit(target,attack);
                }
                remBit(source,board);
            }
        }
        if(!side? i==K:i==k){
            cout<<endl;
            cout<<"--------- Generating King Move --------"<<endl;

            while(board){
                source=lsb_ind(board);
                attack=king_attacks_table[source] & (!side? ~color_bitboards[WHITE]: ~color_bitboards[BLACK]);
                string s=index_to_square(source);
                while(attack){
                    target=lsb_ind(attack);
                    if(is_sq_attacked(target,(side? WHITE:BLACK))){
                        remBit(target,attack);
                        continue;
                    }
                    else if(getBit(target)){
                        cout<<s<<"x"<<index_to_square(target)<<endl;
                    }
                    else{
                        cout<<s<<index_to_square(target)<<endl;
                    }
                    remBit(target,attack);
                }
                remBit(source,board);
            }
        }
    }


}