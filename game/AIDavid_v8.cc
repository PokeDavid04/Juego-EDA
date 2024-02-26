#include "Player.hh"
#include <set>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME David_v8


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
    static Player* factory () {
        return new PLAYER_NAME; 
    }

    int long_vision_p = 4; //4 Por defecto

    void mirar(int id, Pos p){
        Pos p2 = p + BR;
        Pos p3 = p2 + Bottom;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, BR);
        p3 = p2 + Right;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, BR);

        p2 = p + RT;
        p3 = p2 + Right;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, RT);
        p3 = p2 + Top;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, RT);

        p2 = p + TL;
        p3 = p2 + Top;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, TL);
        p3 = p2 + Left;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, TL);

        p2 = p + LB;
        p3 = p2 + Left;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, LB);
        p3 = p2 + Bottom;
        if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, LB);
    }

    Dir dir(Pos p, Pos p2){                                     //Devuelve la direccion que tiene que seguir para llegar de p a p2
        if (p2.i < p.i) {
            if (p2.j < p.j) return TL;
            else if (p2.j > p.j) return RT;
            else return Top;
        } 
        else if (p2.i > p.i) {
            if (p2.j < p.j) return LB;
            else if (p2.j > p.j) return BR;
            else return Bottom;
        } 
        else {
            if (p2.j < p.j) return Left;
            else if (p2.j > p.j) return Right;
        }
        return None; // Si p y p2 son la misma posición
    }

    bool huir(int id, Dir d, UnitType enemigo){                 //Devuelve false si no se puede mover, cierto si consigue huir
        Pos p = unit(id).pos;
        int aux = (int)d;
        int dir_ideal = (aux+4)%8;
        Cell c_ideal = cell(p+(Dir)dir_ideal);

        //Comprobar direccion ideal. Si puedo ir y no es mia voy
        if(c_ideal.type==Cave && c_ideal.id==-1 && c_ideal.owner!=me()){
            command(id, (Dir)dir_ideal);
            return true;
        }

        //Comprobar direcciones un poco menos ideales. Si puedo ir y no es mia voy
        int dir_aux = (aux+3)%8;
        Cell c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
            command(id, (Dir)dir_aux);
            return true;
        }
        dir_aux = (aux+5)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
            command(id, (Dir)dir_aux);
            return true;
        }

        //Si es una esquina comprobar direcciones aceptables. Si puedo ir y no es mia voy
        if(aux%2!=0){
            dir_aux = (aux+2)%8;
            c_aux = cell(p+(Dir)dir_aux);
            if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
                command(id, (Dir)dir_aux);
                return true;
            }
            dir_aux = (aux+7)%8;
            c_aux = cell(p+(Dir)dir_aux);
            if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
                command(id, (Dir)dir_aux);
                return true;
            }
        }


        //Lo mismo pero sin tener en cuenta colores
        if(c_ideal.type==Cave && c_ideal.id==-1){
            command(id, (Dir)dir_ideal);
            return true;
        }
        dir_aux = (aux+3)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1){
            command(id, (Dir)dir_aux);
            return true;
        }
        dir_aux = (aux+5)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1){
            command(id, (Dir)dir_aux);
            return true;
        }
        if(aux%2!=0){
            dir_aux = (aux+2)%8;
            c_aux = cell(p+(Dir)dir_aux);
            if(c_aux.type==Cave && c_aux.id==-1){
                command(id, (Dir)dir_aux);
                return true;
            }
            dir_aux = (aux+7)%8;
            c_aux = cell(p+(Dir)dir_aux);
            if(c_aux.type==Cave && c_aux.id==-1){
                command(id, (Dir)dir_aux);
                return true;
            }
        }
        
        //Si no ha encontrado ninguna posicion para huir y no se ha movido
        return false;
    }

    bool ir_hacia(int id, Dir d){                               //Devuelve false si no se puede mover, cierto si consigue avanzar
        Pos p = unit(id).pos;
        int dir_ideal = (int)d;
        Cell c_ideal = cell(p+d);

        //Si yendo recto se puede ir y no esta pintado por mi, voy
        if(c_ideal.type==Cave && c_ideal.id==-1 && c_ideal.owner!=me()){
            command(id, d);
            return true;
        }
        //Si no voy por el lado que no esta pintado por mi
        int dir_aux = (dir_ideal+1)%8;
        Cell c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
            command(id, (Dir)dir_aux);
            return true;
        }
        dir_aux = (dir_ideal-1)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1 && c_aux.owner!=me()){
            command(id, (Dir)dir_aux);
            return true;
        }

        //Si todas estan pintadas voy por la primera por la que pueda pasar
        if(c_ideal.type==Cave && c_ideal.id==-1){
            command(id, d);
            return true;
        }
        //Si no voy por el lado que no esta pintado por mi
        dir_aux = (dir_ideal+1)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1){
            command(id, (Dir)dir_aux);
            return true;
        }
        dir_aux = (dir_ideal-1)%8;
        c_aux = cell(p+(Dir)dir_aux);
        if(c_aux.type==Cave && c_aux.id==-1){
            command(id, (Dir)dir_aux);
            return true;
        }
        
        //Si no puede ir en esa direccion y no se ha movido
        return false;
    }

  /**
   * Types and attributes for your player can be defined here.
   */
    typedef vector<int> VI;                 //Vector de id's para mis furyans

  /**
   * Play method, invoked once per each round.
   */
    void move_furyans(){
        VI F = furyans(me());                   //Meter los id's de los furyans en el vector
        int n = F.size();                       //Guardar cuantos furyans tengo
        VI perm = random_permutation(n);        //Seleccionar el orden de tratamiento de los furyans (aqui random)

        for(int id : F){                 //Iteramos para cada furyan
            Pos p = unit(id).pos;
            Pos p2 = p;
            set<Pos> visitados;

            for(int i=0; i<8; ++i){               //Movorse a la primera en la que haya alguien
                p2 = p + (Dir)i;
                if(cell(p2).type==Cave && cell(p2).id!=-1 && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer) && unit(cell(p2).id).player != me()) command(id, (Dir)i);
                visitados.insert(p2);
            }

            for(int i=0; i<8; ++i){
                p2 = p+ (Dir)i;
                if(cell(p2).type==Cave){
                    Pos p3;
                    for(int j=0; j<8; ++j){
                        p3 = p2+ (Dir)j;
                        if(visitados.find(p3) != visitados.end()){
                            if(cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, (Dir)i);
                            visitados.insert(p3);
                        }
                    }
                }
            }

            for(int i=0; i<8; ++i){               //Mirar en estrella alguna con enemigo (lejos)
                p2 = p + (Dir)i;
                Pos p3 = p2 + (Dir)i;
                if(cell(p2).type==Cave && cell(p3).type==Cave && cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) command(id, (Dir)i);
            }

            mirar(id, p);

            for(int i=0; i<20; ++i){               //Movorse random
                int r = random(0,7);
                p2 = p + (Dir)r;
                if(cell(p2).type==Cave) command(id, (Dir)r);
            }
        }
    }


    void move_pioneers(){
        vector<int> P = pioneers(me());         //Vector de id's para mis pioneer

        for (int id : P){                       //Iteramos para cada pioneer
            Pos p = unit(id).pos;
            Pos p2 = p + LB;

            vector<set<Pos>> posiciones_posibles(long_vision_p+1);        //La posicion 0 no la miramos
            vector<set<Pos>> posiciones_furyans(long_vision_p+1);         //La posicion 0 no la miramos
            vector<set<Pos>> posiciones_hellhounds(long_vision_p+1);      //La posicion 0 no la miramos

            for(int i=1; i<=long_vision_p; ++i){ //Comprobar en "espiral"
                for(int j=0; j<i*2;++j){
                    if(cell(p2).type == Cave){
                        if(cell(p2).id==-1 && cell(p2).owner!=me()) posiciones_posibles[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Furyan && unit(cell(p2).id).player!=me()) posiciones_furyans[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Hellhound && unit(cell(p2).id).player!=me()) posiciones_hellhounds[i].insert(p2);
                    }     
                    p2+=Top;
                }
                for(int j=0; j<i*2;++j){
                    if(cell(p2).type == Cave){
                        if(cell(p2).id==-1 && cell(p2).owner!=me()) posiciones_posibles[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Furyan && unit(cell(p2).id).player!=me()) posiciones_furyans[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Hellhound && unit(cell(p2).id).player!=me()) posiciones_hellhounds[i].insert(p2);
                    }
                    p2+=Right;
                }
                for(int j=0; j<i*2;++j){
                    if(cell(p2).type == Cave){
                        if(cell(p2).id==-1 && cell(p2).owner!=me()) posiciones_posibles[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Furyan && unit(cell(p2).id).player!=me()) posiciones_furyans[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Hellhound && unit(cell(p2).id).player!=me()) posiciones_hellhounds[i].insert(p2);
                    }
                    p2+=Bottom;
                }
                for(int j=0; j<i*2;++j){
                    if(cell(p2).type == Cave){
                        if(cell(p2).id==-1 && cell(p2).owner!=me()) posiciones_posibles[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Furyan && unit(cell(p2).id).player!=me()) posiciones_furyans[i].insert(p2);
                        else if(cell(p2).id!=-1 && unit(cell(p2).id).type==Hellhound && unit(cell(p2).id).player!=me()) posiciones_hellhounds[i].insert(p2);
                    }
                    p2+=Left;
                }
                p2+=LB;
            }

            bool movido = false;

            for(int i=2; i<=long_vision_p; ++i){
                while(!posiciones_hellhounds[i].empty() && !movido){
                    Dir d = dir(p, *posiciones_hellhounds[i].begin());  //Mira hacia que direccion está el enemigo
                    movido = huir(id, d, Hellhound);                    //Huye de esa direccion
                    posiciones_hellhounds[i].erase(posiciones_hellhounds[i].begin());
                }
            }

            for(int i=1; i<=3; ++i){
                while(!posiciones_furyans[i].empty() && !movido){
                    Dir d = dir(p, *posiciones_furyans[i].begin());  //Mira hacia que direccion está el enemigo
                    movido = huir(id, d, Furyan);                    //Huye de esa direccion
                    posiciones_furyans[i].erase(posiciones_furyans[i].begin());
                }
            }

            for(int i=1; i<=long_vision_p; ++i){
                while(!posiciones_posibles[i].empty() && !movido){
                    Dir d = dir(p, *posiciones_posibles[i].begin());
                    movido = ir_hacia(id, d);
                    posiciones_posibles[i].erase(posiciones_posibles[i].begin());
                }
            }
 
            for(int i=0; i<20; ++i){
                int r=random(0,7);
                if(!movido && cell(p+(Dir)r).type==Cave){
                    command(id, (Dir)r);
                    movido = true;
                }
            }
        }
        //cerr << status(me()) << endl;
    }


    virtual void play(){
        move_furyans();
        move_pioneers();
    }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
