#include "Player.hh"
#include <set>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME David_v7


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME; 
  }
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
      Pos p2 = p;
      set<Pos> visitados;
      set<Dir> prioridad1;
      set<Dir> prioridad2;
      set<Dir> prioridad3;
      set<Dir> dirpeligrosa;
      set<Dir> dirmuypeligrosa;

      for(int i=0; i<8; ++i){               //Movorse a la primera disponible que vea sin pintar
        p2 = p + (Dir)i;
        if(cell(p2).type==Cave){
          if(cell(p2).owner!=me() && cell(p2).id == -1) prioridad1.insert((Dir)i);
          if(cell(p2).id!=-1 && unit(cell(p2).id).type == Furyan && unit(cell(p2).id).player != me()){
            //dirmuypeligrosa.insert((Dir)((i-2)%8));
            dirmuypeligrosa.insert((Dir)((i-1)%8));
            dirmuypeligrosa.insert((Dir)((i)%8));
            dirmuypeligrosa.insert((Dir)((i+1)%8));
            //dirmuypeligrosa.insert((Dir)((i+2)%8));
            //dirpeligrosa.insert((Dir)i);
          } 
          if(cell(p2).id!=-1 && unit(cell(p2).id).type == Pioneer && unit(cell(p2).id).player != me()){
            dirpeligrosa.insert((Dir)i);
          }
        }
        visitados.insert(p2);
      }

      for(int i=0; i<8; ++i){               //Mirar en estrella alguna sin pintar (lejos)
        p2 = p + (Dir)i;
        if(cell(p2).type==Cave){
          Pos p3;
          for(int j=0; j<8; ++j){
            p3 = p2 + (Dir)j;
            if(visitados.find(p3) != visitados.end() && cell(p3).type==Cave){
              if(cell(p3).owner!=me() && cell(p3).id == -1) prioridad2.insert((Dir)i);
              if(cell(p3).id!=-1 && (unit(cell(p3).id).type == Furyan || unit(cell(p3).id).type == Pioneer) && unit(cell(p3).id).player != me()) dirpeligrosa.insert((Dir)i);
              if(cell(p3).id!=-1 && unit(cell(p3).id).type == Hellhound && unit(cell(p3).id).player != me()){
                dirmuypeligrosa.insert((Dir)((i-2)%8));
                dirmuypeligrosa.insert((Dir)((i-1)%8));
                dirmuypeligrosa.insert((Dir)((i)%8));
                dirmuypeligrosa.insert((Dir)((i+1)%8));
                dirmuypeligrosa.insert((Dir)((i+2)%8));
                //dirpeligrosa.insert((Dir)i);
              }
              visitados.insert(p3);
              
              Pos p4;
              for(int k=0; k<8; ++k){
                p4 = p3 + (Dir)k;
                if(visitados.find(p4) != visitados.end() && cell(p4).type==Cave){
                  if(cell(p4).owner!=me() && cell(p4).id == -1) prioridad3.insert((Dir)i);
                  if(cell(p4).id!=-1 && (unit(cell(p4).id).type == Furyan || unit(cell(p4).id).type == Pioneer) && unit(cell(p4).id).player != me()) dirpeligrosa.insert((Dir)i);
                  visitados.insert(p4);
                }
              }
            }
          }
        }
      }

      if(!dirmuypeligrosa.empty()){
        set<Dir> prio1 = prioridad1;
        prio1 = prioridad1;
        while(!prio1.empty()){
          if(dirmuypeligrosa.find(*prio1.begin()) == dirmuypeligrosa.end()) command(id,*prio1.begin()); //Si no es una direccion peligros ves hacia alli
          prio1.erase(prio1.begin());
        }

        for(int i=0; i<8; ++i){
          if(cell(p+(Dir)i).type==Cave && dirmuypeligrosa.find((Dir)i) == dirmuypeligrosa.end()) command(id, (Dir)i);
        }
      }
      
     
      set<Dir> prio1 = prioridad1;
      prio1 = prioridad1;
      Dir bestdir = None;
      while(!prio1.empty()){
        if(dirpeligrosa.find(*prio1.begin()) == dirpeligrosa.end()){
          if(bestdir==None) bestdir = *prio1.begin();
          else if(cell(p+bestdir).owner == -1 && cell(p+*prio1.begin()).owner != -1) bestdir = *prio1.begin();
          else if(cell(p+bestdir).owner != -1 && cell(p+*prio1.begin()).owner != -1 && nb_cells((cell(p+bestdir).owner)) < nb_cells(cell(p+*prio1.begin()).owner)) bestdir = *prio1.begin();
        }  
        prio1.erase(prio1.begin());
      }
      if(bestdir!=None) command(id, bestdir); //Si no es una direccion peligrosa ves hacia alli

      /*set<Dir> prio2 = prioridad2;
      prio2 = prioridad2;
      bestdir = None;
      while(!prio2.empty()){
        if(dirpeligrosa.find(*prio2.begin()) == dirpeligrosa.end()){
          if(bestdir==None) bestdir = *prio2.begin();
          else if(cell(p+bestdir).owner == -1 && cell(p+*prio2.begin()).owner != -1) bestdir = *prio2.begin();
          else if(cell(p+bestdir).owner != -1 && cell(p+*prio2.begin()).owner != -1 && nb_cells((cell(p+bestdir).owner)) < nb_cells(cell(p+*prio2.begin()).owner)) bestdir = *prio2.begin();
        }  
        prio2.erase(prio2.begin());
      }
      if(bestdir!=None) command(id, bestdir); //Si no es una direccion peligrosa ves hacia alli

      set<Dir> prio3 = prioridad3;
      prio3 = prioridad3;
      bestdir = None;
      while(!prio3.empty()){
        if(dirpeligrosa.find(*prio3.begin()) == dirpeligrosa.end()){
          if(bestdir==None) bestdir = *prio3.begin();
          else if(cell(p+bestdir).owner == -1 && cell(p+*prio3.begin()).owner != -1) bestdir = *prio3.begin();
          else if(cell(p+bestdir).owner != -1 && cell(p+*prio3.begin()).owner != -1 && nb_cells((cell(p+bestdir).owner)) < nb_cells(cell(p+*prio3.begin()).owner)) bestdir = *prio3.begin();
        }  
        prio3.erase(prio3.begin());
      }
      if(bestdir!=None) command(id, bestdir); //Si no es una direccion peligrosa ves hacia alli*/

      prio1 = prioridad1;
      while(!prio1.empty()){
        if(dirpeligrosa.find(*prio1.begin()) == dirpeligrosa.end()) command(id,*prio1.begin()); //Si no es una direccion peligros ves hacia alli
        prio1.erase(prio1.begin());
      }

      set<Dir> prio2 = prioridad2;
      while(!prio2.empty()){
        if(dirpeligrosa.find(*prio2.begin()) == dirpeligrosa.end()) command(id,*prio2.begin()); //Si no es una direccion peligros ves hacia alli
        prio2.erase(prio2.begin());
      }

      set<Dir> prio3 = prioridad3;
      while(!prio3.empty()){
        if(dirpeligrosa.find(*prio3.begin()) == dirpeligrosa.end()) command(id,*prio3.begin()); //Si no es una direccion peligros ves hacia alli
        prio3.erase(prio3.begin());
      }

      if(!prioridad1.empty()) command(id,*prioridad1.begin()); //Si no hay ninguna segura a la primera que vea sin pintar
      if(!prioridad2.empty()) command(id,*prioridad2.begin());
      if(!prioridad3.empty()) command(id,*prioridad3.begin());

      for(int i=0; i<10; ++i){               //Movorse random
        int r = random(0,7);
        p2 = p + (Dir)r;
        if(cell(p2).type==Cave && cell(p2).id == -1 && dirpeligrosa.find((Dir)r) == dirpeligrosa.end()) command(id, (Dir)r);
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
