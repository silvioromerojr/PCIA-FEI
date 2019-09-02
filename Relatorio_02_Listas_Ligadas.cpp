/*PROGRAMACAO CIENTÍFICA - PEL216
 ALUNO: Silvio Romero de Araújo Júnior  RA: 118324-3
 PROFESSOR: Reinaldo Bianchi
 RELATORIO 2 - Listas Ligadas
 PROGRAMA PLISTAS LIGADAS*/
#include <iostream>

using namespace std;

// classe Nó
class No
{
private:
    int valor;
    No* proximo;
public:
    No(int valor) // construtor
    {
        this->valor = valor;
        this->proximo = NULL;
    }
    
    int obterValor() // obtém o valor a ser inserido na lista
    {
        return valor;
    }
    
    No* obterproximo() // obtém o próximo Nó
    {
        return proximo;
    }
    
    void setproximo(No* p) // seta o próximo Nó
    {
        proximo = p;
    }
};

// classe Lista
class Lista
{
private:
    No* head; // primeiro elemento
    No* tail; // último elemento
    
public:
    Lista()
    {
        // se não passar elemento, então head e tail são NULL
        head = NULL;
        tail = NULL;
    }
    
    Lista(int valor)
    {
        // se passar elemento, então cria novo Nó
        // Tratamento de Exececao - Try and Catch
        try {
            head = new No(valor);
            
        }
        catch (...)
        {
            cerr << "Nao foi possivel alocar a memoria solicitada!." << endl << endl;
            exit(1);
        }
        tail = head;
    }
    
    virtual ~Lista() // destrutor
    {
        cout << "Lista apagada!" << endl;
        delete head;
    }
    
    void mostrar() // mostra todos os elementos da lista
    {
        cout << "\nImprimindo todos os elementos...\n";
        No* c = head;
        
        if(vazia())
            cout << "A lista NAO possui elementos!!\n";
        else
        {
            while(c) // percorre a lista
            {
                cout << c->obterValor() << endl;
                c = c->obterproximo();
            }
            cout << endl;
        }
    }
    
    bool vazia() // verifica se a lista está vazia
    {
        return (head == NULL);
    }
    
    // insere no início
    void inserir_inicio(int valor)
    {
        No* novo_no = new No(valor);
        
        if(vazia())
        {
            head = novo_no;
            tail = novo_no;
        }
        else
        {
            novo_no->setproximo(head);
            head = novo_no;
        }
    }
    
    // insere no final
    void inserir_final(int valor)
    {
        No* novo_no = new No(valor);
        
        if(vazia())
        {
            head = novo_no;
            tail = novo_no;
        }
        else
        {
            tail->setproximo(novo_no);
            tail = novo_no;
        }
    }
    
    // retorna o tamanho da lista
    int tamanho()
    {
        if(vazia()) // se for vazia, então retorna 0
            return 0;
        
        No* c = head;
        int tam = 0;
        
        // percorre a lista
        do
        {
            c = c->obterproximo();
            tam++;
        }
        while(c);
        
        return tam;
    }
    
    // verifica se um elemento existe na lista
    bool existe(int valor)
    {
        No* c = head;
        
        while(c)
        {
            if(c->obterValor() == valor)
                return true;
            c = c->obterproximo();
        }
        return false;
    }
    
    // remove da lista, remoção do final
    void remover()
    {
        if(!vazia())
        {
            // se houver só 1 elemento
            if(head->obterproximo() == NULL)
                head = NULL;
            else if(head->obterproximo()->obterproximo() == NULL) // 2 elementos
                head->setproximo(NULL);
            else // > 2 elementos
            {
                No* ant_ant = head;
                No* ant = head->obterproximo();
                No* atual = head->obterproximo()->obterproximo();
                
                while(atual)
                {
                    No* aux = ant;
                    ant = atual;
                    ant_ant = aux;
                    atual = atual->obterproximo();
                }
                delete ant_ant->obterproximo(); // libera memória
                ant_ant->setproximo(NULL); // seta o proximo como NULL
                tail = ant_ant; // atualiza a tail
            }
        }
    }
};

int main()
{
    Lista lista;
    
    if(lista.vazia())
        cout << "Lista vazia!!\n";
    else
        cout << "Lista NAO vazia!!\n";
    
    lista.mostrar();
    
    if(lista.existe(10))
        cout << "\nO elemento 10 existe na lista!!\n";
    else
        cout << "\nO elemento 10 NAO existe na lista!!\n";
    
    lista.inserir_final(10);
    lista.inserir_final(20);
    lista.inserir_final(30);
    lista.inserir_final(40);
    lista.inserir_inicio(50);
    
    lista.mostrar();
    
    if(lista.vazia())
        cout << "Lista vazia!!\n";
    else
        cout << "Lista NAO vazia!!\n";
    
    if(lista.existe(10))
        cout << "\nO elemento 10 existe na lista!!\n";
    else
        cout << "\nO elemento 10 NAO existe na lista!!\n";
    
    lista.remover();
    
    lista.mostrar();
    
    cout << "Tamanho da lista: " << lista.tamanho() << endl;
    
    return 0;
}
