/*
Joao Luis Chiarelotto Crema

ENUNCIADO
    Sua  tarefa  será  construir  um  graph,  com  10  vértices  cujos  valores  serão  aleatoriamente 
selecinados em um conjunto de inteiros contendo números inteiros entre 1 e 1000. Cada vértice terá 
um número aleatório de arestas menor ou igual a três.  
    Você  deverá  criar  este  graph,  armazeneo  estes  vértices  e  arestas  em  uma  tabela  de 
adjacências e em uma Listaa de adjacências, medindo o tempo necessário para criar estas estruturas de 
dados. Estas duas tabelas deverão ser salvas em arquivos de texto chamados de tabela_adjacencias.txt 
e Listaa_adjacencias.txt respectivamente. Estes arquivos devem ser salvos no site repl.it 
Para que seja possível verificar as diferenças de tempos de criação destas estruturas, uma vez 
que o algoritmo esteja pronto, você deverá mudar o tamanho do gráfico para 100.000 de itens e repetir 
o processo de ciração no mínimo 50 vezes, anoteo os tempos de criação apresenteo estas médias 
para a tabela de adjacencias e para a Listaa de adjacencias. 

Esse nao deu mesmo, nao consegui salvar a lista que fiz, nem cheguei a fazer matriz, o codigo a seguir e o resultado
de 3 semanas de um aluno tentando entender como funciona essa *****.
*/

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <chrono> //LEMBRAR DE MARCAR OS TEMPOS, RECRIAR E MARCAR 50X
using namespace std;

class Edge;
class Vertex;

class Edge {
  public:
    int DestinationVertexID;
  int weight;

  Edge() {}
  Edge(int destVID, int w) {
    DestinationVertexID = destVID;
    weight = w;
  }
  void setEdgeValues(int destVID, int w) {
    DestinationVertexID = destVID;
    weight = w;
  }
  void setWeight(int w) {
    weight = w;
  }

  int getDestinationVertexID() {
    return DestinationVertexID;
  }
  int getWeight() {
    return weight;
  }
};

class Vertex {
  public:
    int state_id;
  string state_name;

  list < Edge > edgeList;

  Vertex() {
    state_id = 0;
    state_name = "";
  }

  Vertex(int id, string sname) {
    state_id = id;
    state_name = sname;
  }

  int getStateID() {
    return state_id;
  }
  string getStateName() {
    return state_name;
  }
  void setID(int id) {
    state_id = id;
  }
  void setStateName(string sname) {
    state_name = sname;
  }

  list < Edge > getEdgeList() {
    return edgeList;
  }

  //  void addEdgeToEdgelist(int toVertexID, int weight)
  //  {
  //	  	Edge e(toVertexID,weight);
  //		edgeList.push_back(e); 
  //		cout<<"Edge between "<<state_id<<" and "<<toVertexID<<" added Successfully"<<endl; 	
  //    "cu"
  //  }

  void printEdgeList() {
    cout << "[";
    for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
      cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
    }
    cout << "]";
    cout << endl;
  }

  void updateVertexName(string sname) {
    state_name = sname;
    cout << "Nome da vertice alterado com sucesso";
  }

};

class Graph {

  vector < Vertex > vertices;

  public:

    bool checkIfVertexExistByID(int vid) {
      bool flag = false;
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == vid) {
          return true;
        }
      }
      return flag;
    }

  void addVertex(Vertex newVertex) {
    bool check = checkIfVertexExistByID(newVertex.getStateID());
    if (check == true) {
      cout << "Vertice com esse ID ja existe" << endl;
    } else {
      vertices.push_back(newVertex);
      cout << "Novo vertice adicionado com sucesso" << endl;
    }
  }

  Vertex getVertexByID(int vid) {
    Vertex temp;
    for (int i = 0; i < vertices.size(); i++) {
      temp = vertices.at(i);
      if (temp.getStateID() == vid) {
        return temp;
      }
    }
    return temp;
  }

  bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
    Vertex v = getVertexByID(fromVertex);
    list < Edge > e;
    e = v.getEdgeList();
    bool flag = false;
    for (auto it = e.begin(); it != e.end(); it++) {
      if (it -> getDestinationVertexID() == toVertex) {
        flag = true;
        return flag;
        break;
      }

    }
    return flag;
  }

  void updateVertex(int oldVID, string vname) { //Isso nao era pra estar funcionando
    bool check = checkIfVertexExistByID(oldVID);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == oldVID) {
          vertices.at(i).setStateName(vname);
          break;
        }
      }
      cout << "Vertice atualizado " << endl;
    }
  }

  void addEdgeByID(int fromVertex, int toVertex, int weight) {
    bool check1 = checkIfVertexExistByID(fromVertex);
    bool check2 = checkIfVertexExistByID(toVertex);

    bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
    if ((check1 && check2 == true)) {

      if (check3 == true) {
        cout << "Edge entre " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") e " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") ja existe" << endl;
      } else {

        for (int i = 0; i < vertices.size(); i++) {

          if (vertices.at(i).getStateID() == fromVertex) {
            Edge e(toVertex, weight);
            //edgeList.push_back(e); 
            //vertices.at(i).addEdgeToEdgelist(toVertex,weight);
            vertices.at(i).edgeList.push_back(e);
          } else if (vertices.at(i).getStateID() == toVertex) {
            Edge e(toVertex, weight);
            //edgeList.push_back(e); 
            //vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
            vertices.at(i).edgeList.push_back(e);
          }
        }

        cout << "Edge entre " << fromVertex << " e " << toVertex << " adicionada com sucesso" << endl;
      }
    } else {
      cout << "ID do vertice invalido.";
    }
  }

  void updateEdgeByID(int fromVertex, int toVertex, int newWeight) {
    bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {

        if (vertices.at(i).getStateID() == fromVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == toVertex) {
              it -> setWeight(newWeight);
              break;
            }

          }

        } else if (vertices.at(i).getStateID() == toVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == fromVertex) {
              it -> setWeight(newWeight);
              break;
            }

          }
        }
      }
      cout << "Peso do caminho atualizado com sucesso " << endl;
    } else {
      cout << "Edge entre " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") e " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") NAO existe" << endl; //concatenar strings e variaveis e um porre
    }
  }

  void deleteEdgeByID(int fromVertex, int toVertex) { //saco de funcao, arrumar linha 248-251
    bool check = checkIfEdgeExistByID(fromVertex, toVertex);
    if (check == true) {
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == fromVertex) {
          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == toVertex) {
              vertices.at(i).edgeList.erase(it);
              //cout<<"First erase"<<endl;
              break;
            }
          }
        }

        if (vertices.at(i).getStateID() == toVertex) { //arrumar... tudo

          for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == fromVertex) {
              vertices.at(i).edgeList.erase(it);
              //cout<<"second erase"<<endl;
              break;
            }
          }
        }
      }
      cout << "Edge Between " << fromVertex << " and " << toVertex << " Deletado com sucesso." << endl;
    }
  }

  void deleteVertexByID(int vid) {
    int vIndex = 0;
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices.at(i).getStateID() == vid) {
        vIndex = i;
      }
    }
    for (int i = 0; i < vertices.size(); i++) {
      for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
        if (it -> getDestinationVertexID() == vid) {
          vertices.at(i).edgeList.erase(it);
          break;
        }
      }

    }
    vertices.erase(vertices.begin() + vIndex);
    cout << "Vertice deletado com sucesso" << endl;
  }

  void getAllNeigborsByID(int vid) { //finalmente ta pront
    cout << getVertexByID(vid).getStateName() << " (" << getVertexByID(vid).getStateID() << ") --> ";
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices.at(i).getStateID() == vid) {
        cout << "[";
        for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
          cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
        }
        cout << "]";

      }
    }

  }

  void printGraph() { //ver se e assim q tem q imprimir
    for (int i = 0; i < vertices.size(); i++) {
      Vertex temp;
      temp = vertices.at(i);
      cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
      temp.printEdgeList();
    }
  }

};

int main() {
  Graph g;
  string sname;
  int id1, id2, w;
  int option;
  bool check;

  do {
      cout << " Selecione a operacao desejada, 0 para sair" << endl;
    cout << "1. Adiciona vertice" << endl;
    cout << "2. Atualiza Vertice" << endl;
    cout << "3. Deleta vertice" << endl;
    cout << "4. Adiciona Edge" << endl;
    cout << "5. Atualiza Edge" << endl;
    cout << "6. Deleta Edge" << endl;
    cout << "7. Check se 2 vertices sao vizinhas" << endl;
    cout << "8. Print todos os vizinhos de um vertice" << endl;
    cout << "9. Print Graph" << endl;
    cout << "0. Exit Program" << endl;

    cin >> option;
    Vertex v1;

    switch (option) {
    case 0:

      break;

    case 1:
      cout << "Operacao adiciona vertice -" << endl;
      cout << "Digite o State ID :";
      cin >> id1;
      cout << "Digite o nome :";
      cin >> sname;
      v1.setID(id1);
      v1.setStateName(sname);
      g.addVertex(v1);
      
      break;

    case 2:
      cout << "Atualiza vertice -" << endl;
      cout << "ID do vertice a ser atualizado :";
      cin >> id1;
      cout << "Digite State Nome :";
      cin >> sname;
      g.updateVertex(id1, sname);

      break;

    case 3:
      cout << "Deleta vertice -" << endl;
      cout << "Digite o ID do vertice a ser deletado : ";
      cin >> id1;
      g.deleteVertexByID(id1);

      break;

    case 4:
      cout << "Adiciona Edge -" << endl;
      cout << "Digite o ID de origem: ";
      cin >> id1;
      cout << "Digite o ID de destino ";
      cin >> id2;
      cout << "Digite o peso da Edge ";
      cin >> w;
      g.addEdgeByID(id1, id2, w);

      break;

    case 5:
      cout << "Atualiza a Egdge -" << endl;
      cout << "Digite o ID de origem: ";
      cin >> id1;
      cout << "Digite o ID de destino: ";
      cin >> id2;
      cout << "Digite o peso da Edge atualizado: ";
      cin >> w;
      g.updateEdgeByID(id1, id2, w);

      break;

    case 6:
      cout << "Deleta Edge -" << endl;
      cout << "Digite o ID de origem: ";
      cin >> id1;
      cout << "Digite o ID de destino: ";
      cin >> id2;
      g.deleteEdgeByID(id1, id2);

      break;

    case 7:
      cout << "Check se 2 vertices sao vizinhas -" << endl;
      cout << "Digite o ID de origem: ";
      cin >> id1;
      cout << "Digite o ID de destino: ";
      cin >> id2;
      check = g.checkIfEdgeExistByID(id1, id2);
      if (check == true) {
        cout << "Vertices vizinhas";
      } else {
        cout << "Vertices NAO sao vizinhas";
      }

      break;

    case 8:
      cout << "Print todos os vizinhos de um vertice-" << endl;
      cout << "Digite o ID do vertice: ";
      cin >> id1;
      g.getAllNeigborsByID(id1);

      break;

    case 9:
      cout << "Print Graph -" << endl;
      g.printGraph();

      break;

    default:
      cout << "Digite uma operacao valida" << endl;
    }
    cout << endl;

  } while (option != 0);

  return 0;
}
