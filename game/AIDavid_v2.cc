#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME David_v2


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  int long_vision_p = 2;                  //Maximo de casillas que mira a cada lado un Pioneer
  int long_vision_f = 10;                  //Maximo de casillas que mira a cada lado un 
  typedef vector<int> VI;                 //Vector de id's para mis furyans

  int direc(Pos p, Pos p2){       //Devuelve la direccion que hay que seguir para llegar de p a p2 (algoritmo A*)
    string dir;
    if(p.i > p2.i){ //abajo
      if(p.j > p2.j) return LB;
      else if(p.j < p2.j) return TL;
      else return Left;
    }
    else if(p.i < p2.i){ //arriba
      if(p.j > p2.j) return BR;
      else if(p.j < p2.j) return RT;
      else return Right;
    }
    else{ //misma fila
      if(p.j > p2.j) return Bottom;
      else if(p.j < p2.j) return Top;
      else return 1;
    }
  }

  /**
   * Play method, invoked once per each round.
   */
  void move_furyans(){
    VI F = furyans(me());                   //Meter los id's de los furyans en el vector
    int n = F.size();                       //Guardar cuantos furyans tengo
    VI perm = random_permutation(n);        //Seleccionar el orden de tratamiento de los furyans (aqui random)

    for(int id : F){                 //Iteramos para cada furyan
      //int id = F[perm[i]];
      Pos p = unit(id).pos;
      int id2;
      Pos p2 = p + LB;

      for(int i=1; i<=long_vision_f; ++i){ //Comprobar en "espiral"
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          if(id2!=-1 && unit(id2).player!=me() && cell(p+Dir(direc(p, p2))).type!=Rock) command(id, Dir(direc(p, p2)));//Mover hacia esa direccion
          p2+=Top;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          if(id2!=-1 && unit(id2).player!=me() && cell(p+Dir(direc(p, p2))).type!=Rock) command(id, Dir(direc(p, p2)));//Mover hacia esa direccion
          p2+=Right;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          if(id2!=-1 && unit(id2).player!=me() && cell(p+Dir(direc(p, p2))).type!=Rock) command(id, Dir(direc(p, p2)));//Mover hacia esa direccion
          p2+=Bottom;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          if(id2!=-1 && unit(id2).player!=me() && cell(p+Dir(direc(p, p2))).type!=Rock) command(id, Dir(direc(p, p2)));//Mover hacia esa direccion
          p2+=Left;
        }
        p2+=LB;
      }
      for(int i=0; i<8; ++i){
        if(cell(p+Dir(i)).type!=Rock) command(id, Dir(i));
      }
    }
  }


  void move_pioneers(){
    vector<int> P = pioneers(me());         //Vector de id's para mis pioneers
    vector<bool> DirNoSeg(9,false);               //Vector de direcciones (true = no seguras)
    vector<vector<bool>> DirSinPintar(long_vision_p, vector<bool>(9,false));           //Vector de direcciones (true = sin pintar)

    for (int id : P){                       //Iteramos para cada pioneer
      Pos p = unit(id).pos;
      int id2;
      Pos p2 = p;

      for(int i=0; i<8; ++i){               //Comprovar long_vision_p casillas en cada dirección (en "estrella")
        for(int j=0; j<long_vision_p;++j){
          p2+=Dir(i);
          id2 = cell(p2).id;
          if(id2 != -1 && unit(id2).player != me()) DirNoSeg[i] = true; //Si hay un enemigo marcarlo como inseguro
          //Si es muy urgente me podria mover, si no tomo la decision al final
          if(cell(p2).owner != me()) DirSinPintar[j][i] = true;
          //Podria distinguir entre posicion vacia y de un oponente vector de int
        }
        p2 = p;
      }

      for(int i=0; i<8; ++i){               //Buscar primer sitio libre donde no haya un enemigo
        for(int j=0; j<long_vision_p;++j){
          if(DirSinPintar[j][i] && !DirNoSeg[i] && cell(p+Dir(i)).type!=Rock) command(id, Dir(i));
        }
      }

      //Si no hay nada cerca posicion "random"
      for(int i=0; i<8; ++i){
        if(cell(p+Dir(i)).type!=Rock) command(id, Dir(i));
      }
    }
  }

  virtual void play () {
    move_furyans();
    move_pioneers();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
