#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME David_v1


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
  int long_vision_p = 4;                  //Maximo de casillas que mira a cada lado un Pioneer
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

  void IrDireccionContraria(vector<bool> &DirSinPintar, Dir dir, int id){
    switch (dir){
      case Top:
        if(DirSinPintar[Down]) command(id, Down);
        break;
      case Down:
        if(DirSinPintar[Top]) command(id, Top);
        break;
      case Left:
        if(DirSinPintar[Right]) command(id, Right);
        break;
      case Right:
        if(DirSinPintar[Left]) command(id, Left);
        break;
      case TL:
        if(DirSinPintar[BR]) command(id, BR);
        break;
      case RT:
        if(DirSinPintar[LB]) command(id, LB);
        break;
      case LB:
        if(DirSinPintar[RT]) command(id, RT);
        break;
      case BR:
        if(DirSinPintar[TL]) command(id, TL);
        break;
      default:

        break;
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
    vector<bool> DirNoSeg(8,false);               //Vector de direcciones (true = no seguras)
    vector<bool> DirSinPintar(8, false);          //Vector de posiciones adyacentes (true = no es tuya)

    for(int id : P){
      Pos p = unit(id).pos;
      int id2;
      Pos p2 = p;
      int dir;

      //Comprobar cuales de las direcciones cercanas tiene una casilla que no es tuya
      for(int i=0; i<8; ++i){
        p2 = p+ Dir(i);
        if(cell(p2).type!=Rock && cell(p2).owner!=me()) DirSinPintar[i] = true;
      }

      //Buscar enemigos (Cuando encuentra un enemigo y la direccion contraria no es tuya, moverse hacia allí)
      p2 = p+ RT;
      for(int i=1; i<=long_vision_p; ++i){ //Comprobar en "espiral"
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          Dir dir = Dir(direc(p, p2));
          if(cell(p+dir).type!=Rock && id2!=-1 && unit(id2).player!=me() && (unit(id2).type == Furyan || unit(id2).type == Hellhound)){
            IrDireccionContraria(DirSinPintar, dir, id);
          } 
          p2+=Bottom;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          Dir dir = Dir(direc(p, p2));
          if(cell(p+dir).type!=Rock && id2!=-1 && unit(id2).player!=me() && (unit(id2).type == Furyan || unit(id2).type == Hellhound)){
            IrDireccionContraria(DirSinPintar, dir, id);
          } 
          p2+=Left;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          Dir dir = Dir(direc(p, p2));
          if(cell(p+dir).type!=Rock && id2!=-1 && unit(id2).player!=me() && (unit(id2).type == Furyan || unit(id2).type == Hellhound)){
            IrDireccionContraria(DirSinPintar, dir, id);
          } 
          p2+=Top;
        }
        for(int j=0; j<i*2;++j){
          id2 = cell(p2).id;
          Dir dir = Dir(direc(p, p2));
          if(cell(p+dir).type!=Rock && id2!=-1 && unit(id2).player!=me() && (unit(id2).type == Furyan || unit(id2).type == Hellhound)){
            IrDireccionContraria(DirSinPintar, dir, id);
          } 
          p2+=Right;
        }
        p2+=RT;
      }

      //Si no ha encontrado ninguno ir a la posición sin pintar mas cercana
      for(int i: DirSinPintar){
        if(DirSinPintar[i]) command(id, Dir(i));
      }
      //Si no hay ninguna al rededor sin pintar moverse a una direccion que simplemente no sea roca
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
