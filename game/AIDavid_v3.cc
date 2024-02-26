#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME David_v3


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
  typedef vector<int> VI;                 //Vector de id's para mis furyans

  void mirar(int id, Pos p){
      Pos p2 = p + BR;
      Pos p3 = p2 + Top;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, BR);
      p3 = p2 + Left;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, BR);

      p2 = p + RT;
      p3 = p2 + Bottom;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, RT);
      p3 = p2 + Left;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, RT);

      p2 = p + TL;
      p3 = p2 + Bottom;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, TL);
      p3 = p2 + Right;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, TL);

      p2 = p + LB;
      p3 = p2 + Top;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, LB);
      p3 = p2 + Right;
      if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, LB);

  }

  /**
   * Play method, invoked once per each round.
   */
  void move_furyans(){
    VI F = furyans(me());                   //Meter los id's de los furyans en el vector
    int n = F.size();                       //Guardar cuantos furyans tengo
    VI perm = random_permutation(n);        //Seleccionar el orden de tratamiento de los furyans (aqui random)

    for(int id : F){                 //Iteramos para cada furyan
      Pos p = unit(id).pos;
      Pos p2;
      Pos p3;

      for(int i=0; i<8; ++i){               //Movorse a la primera en la que haya alguien
        p2 = p + Dir(i);
        if(cell(p2).type==Cave && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, Dir(i));
      }

      for(int i=0; i<8; ++i){               //Mirar en estrella alguna sin pintar (lejos)
        p2 = p + Dir(i);
        p3 = p2 + Dir(i);
        if(cell(p2).type==Cave && cell(p3).type!=Rock && (unit(cell(p2).id).type == Furyan || unit(cell(p2).id).type == Pioneer)) command(id, Dir(i));
      }
      
      mirar(id, p);
      
      for(int i=0; i<20; ++i){               //Movorse random
        p2 = p+Dir(random(0,7));
        if(cell(p2).type==Cave) command(id, Dir(i));
      }
    }
  }


  void move_pioneers(){
    vector<int> P = pioneers(me());         //Vector de id's para mis pioneer

    for (int id : P){                       //Iteramos para cada pioneer
      Pos p = unit(id).pos;
      Pos p2 = p;

      for(int i=0; i<8; ++i){               //Movorse a la primera disponible que vea sin pintar
        p2 = p + Dir(i);
        if(cell(p2).type==Cave && cell(p2).owner!=me() && cell(p2).id == -1) command(id, Dir(i));
      }

      for(int i=0; i<8; ++i){               //Mirar en estrella alguna sin pintar (lejos)
        p2 = p + Dir(i);
        Pos p3 = p2 + Dir(i);
        if(cell(p2).type==Cave && cell(p3).type!=Rock && cell(p3).owner!=me() && cell(p3).id == -1) command(id, Dir(i));
      }

      for(int i=0; i<20; ++i){               //Movorse random
        p2 = p+Dir(random(0,7));
        if(cell(p2).type==Cave && cell(p2).id == -1) command(id, Dir(i));
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
