// Copyright 2015 Jean Martina

#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "avl_tree.h"

#define TAM1 100
#define TAM2 200
#define INITVAL 10

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class Objeto {};

class NoAVLTest: public ::testing::Test {
 public:
    virtual void SetUp() {
        this->inteiro = new NoAVL<int>(INITVAL);
        this->obj = new NoAVL<Objeto*>(new Objeto());
    }

    virtual void TearDown() {
        delete this->inteiro;
        delete this->obj;
    }

 protected:
    NoAVL<int> *inteiro;
    NoAVL<Objeto*> *obj;
};

// Verifica se a altura de cada nivel esta correta e
// retorna o numero de elementos na arvore
template<typename T>
int verifica_altura_recursivo(NoAVL<T>* arv, int* alt_ret = NULL) {
    if (!arv->getEsquerda() && !arv->getDireita()) {
        EXPECT_EQ(0, arv->getAltura());
        if (alt_ret)
            *alt_ret = 0;
        return 1;
    }

    int esq = -1, dir = -1;
    int nesq = 0, ndir = 0;
    if (arv->getEsquerda())
        nesq = verifica_altura_recursivo(arv->getEsquerda(), &esq);
    if (arv->getDireita())
        ndir = verifica_altura_recursivo(arv->getDireita(), &dir);

    int altura_no_atual = std::max(esq, dir) + 1;
    EXPECT_EQ(altura_no_atual, arv->getAltura());
    if (alt_ret)
        *alt_ret = altura_no_atual;
    return nesq+ndir+1;
}

TEST_F(NoAVLTest, construtor) {
    ASSERT_EQ(0, inteiro->getAltura());
    ASSERT_EQ(INITVAL, *(inteiro->getDado()));
    ASSERT_EQ(1, verifica_altura_recursivo(inteiro));
}


TEST_F(NoAVLTest, insereRotacaoSimplesDireita) {
    inteiro = inteiro->inserir(INITVAL+1, inteiro);
    inteiro = inteiro->inserir(INITVAL+2, inteiro);

    ASSERT_EQ(1, inteiro->getAltura());
    ASSERT_EQ(INITVAL+1, *(inteiro->getDado()));
    ASSERT_EQ(INITVAL, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(INITVAL+2, *(inteiro->getDireita()->getDado()));
}

TEST_F(NoAVLTest, insereRotacaoSimplesEsquerda) {
    inteiro = inteiro->inserir(INITVAL-1, inteiro);
    inteiro = inteiro->inserir(INITVAL-2, inteiro);

    ASSERT_EQ(1, inteiro->getAltura());
    ASSERT_EQ(INITVAL-1, *(inteiro->getDado()));
    ASSERT_EQ(INITVAL-2, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(INITVAL, *(inteiro->getDireita()->getDado()));
}

TEST_F(NoAVLTest, insereRotacaoDuplaEsquerda) {
    inteiro = inteiro->inserir(INITVAL-3, inteiro);
    inteiro = inteiro->inserir(INITVAL-2, inteiro);

    ASSERT_EQ(1, inteiro->getAltura());
    ASSERT_EQ(INITVAL-2, *(inteiro->getDado()));
    ASSERT_EQ(INITVAL-3, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(INITVAL, *(inteiro->getDireita()->getDado()));
}

TEST_F(NoAVLTest, insereRotacaoDuplaDireita) {
    inteiro = inteiro->inserir(INITVAL+2, inteiro);
    inteiro = inteiro->inserir(INITVAL+1, inteiro);

    ASSERT_EQ(1, inteiro->getAltura());
    ASSERT_EQ(INITVAL+1, *(inteiro->getDado()));
    ASSERT_EQ(INITVAL, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(INITVAL+2, *(inteiro->getDireita()->getDado()));
}

TEST_F(NoAVLTest, getAltura) {
    ASSERT_EQ(0, inteiro->getAltura());
    inteiro = inteiro->inserir(INITVAL-2, inteiro);
    inteiro = inteiro->inserir(INITVAL+2, inteiro);
    ASSERT_EQ(1, inteiro->getAltura());

    inteiro = inteiro->inserir(INITVAL-1, inteiro);
    inteiro = inteiro->inserir(INITVAL+1, inteiro);
    ASSERT_EQ(2, inteiro->getAltura());

    inteiro = inteiro->inserir(7, inteiro);
    inteiro = inteiro->inserir(13, inteiro);
    ASSERT_EQ(2, inteiro->getAltura());
}

TEST_F(NoAVLTest, removerRotacaoSimplesDireita) {
    inteiro = inteiro->inserir(5, inteiro);
    inteiro = inteiro->inserir(15, inteiro);
    inteiro = inteiro->inserir(14, inteiro);
    inteiro = inteiro->inserir(16, inteiro);
    inteiro = inteiro->inserir(6, inteiro);
    inteiro = inteiro->inserir(17, inteiro);
    inteiro = inteiro->inserir(13, inteiro);
    inteiro = inteiro->inserir(18, inteiro);
    inteiro = inteiro->inserir(7, inteiro);
    inteiro = inteiro->inserir(8, inteiro);
    inteiro = inteiro->inserir(3, inteiro);
    inteiro = inteiro->inserir(19, inteiro);
    ASSERT_EQ(4, inteiro->getAltura());
    ASSERT_EQ(13, verifica_altura_recursivo(inteiro));
    inteiro = inteiro->remover(inteiro, 15);
    // Rotação simples à Direita

    ASSERT_EQ(3, inteiro->getAltura());
    ASSERT_EQ(12, verifica_altura_recursivo(inteiro));

    EXPECT_EQ(10, *(inteiro->busca(10, inteiro)));
    EXPECT_EQ(5, *(inteiro->busca(5, inteiro)));
    EXPECT_EQ(14, *(inteiro->busca(14, inteiro)));
    EXPECT_EQ(16, *(inteiro->busca(16, inteiro)));
    EXPECT_EQ(6, *(inteiro->busca(6, inteiro)));
    EXPECT_EQ(17, *(inteiro->busca(17, inteiro)));
    EXPECT_EQ(13, *(inteiro->busca(13, inteiro)));
    EXPECT_EQ(18, *(inteiro->busca(18, inteiro)));
    EXPECT_EQ(7, *(inteiro->busca(7, inteiro)));
    EXPECT_EQ(8, *(inteiro->busca(8, inteiro)));
    EXPECT_EQ(3, *(inteiro->busca(3, inteiro)));
    EXPECT_EQ(19, *(inteiro->busca(19, inteiro)));
}

TEST_F(NoAVLTest, removerRotacaoSimplesEsquerda) {
    inteiro = inteiro->inserir(5, inteiro);
    inteiro = inteiro->inserir(15, inteiro);
    inteiro = inteiro->inserir(14, inteiro);
    inteiro = inteiro->inserir(16, inteiro);
    inteiro = inteiro->inserir(6, inteiro);
    inteiro = inteiro->inserir(13, inteiro);
    ASSERT_EQ(3, inteiro->getAltura());
    ASSERT_EQ(7, verifica_altura_recursivo(inteiro));
    inteiro = inteiro->remover(inteiro, 15);

    ASSERT_EQ(2, inteiro->getAltura());
    ASSERT_EQ(6, verifica_altura_recursivo(inteiro));

    EXPECT_EQ(5, *(inteiro->busca(5, inteiro)));
    EXPECT_EQ(6, *(inteiro->busca(6, inteiro)));
    EXPECT_EQ(10, *(inteiro->busca(10, inteiro)));
    EXPECT_EQ(13, *(inteiro->busca(13, inteiro)));
    EXPECT_EQ(14, *(inteiro->busca(14, inteiro)));
    EXPECT_EQ(16, *(inteiro->busca(16, inteiro)));
}

TEST_F(NoAVLTest, removerRotacaoDuplaEsquerda) {
    inteiro = inteiro->inserir(4, inteiro);
    inteiro = inteiro->inserir(15, inteiro);
    inteiro = inteiro->inserir(14, inteiro);
    inteiro = inteiro->inserir(17, inteiro);
    inteiro = inteiro->inserir(6, inteiro);
    inteiro = inteiro->inserir(20, inteiro);
    inteiro = inteiro->inserir(13, inteiro);
    inteiro = inteiro->inserir(25, inteiro);
    inteiro = inteiro->inserir(7, inteiro);
    inteiro = inteiro->inserir(8, inteiro);
    inteiro = inteiro->inserir(2, inteiro);
    inteiro = inteiro->inserir(26, inteiro);
    inteiro = inteiro->inserir(18, inteiro);

    ASSERT_EQ(4, inteiro->getAltura());
    ASSERT_EQ(14, verifica_altura_recursivo(inteiro));

    inteiro = inteiro->remover(inteiro, 26);
    inteiro = inteiro->remover(inteiro, 25);
    // Rotação dupla à Direita
    ASSERT_EQ(3, inteiro->getAltura());
    ASSERT_EQ(12, verifica_altura_recursivo(inteiro));

    EXPECT_EQ(2, *(inteiro->busca(2, inteiro)));
    EXPECT_EQ(4, *(inteiro->busca(4, inteiro)));
    EXPECT_EQ(6, *(inteiro->busca(6, inteiro)));
    EXPECT_EQ(7, *(inteiro->busca(7, inteiro)));
    EXPECT_EQ(8, *(inteiro->busca(8, inteiro)));
    EXPECT_EQ(10, *(inteiro->busca(10, inteiro)));
    EXPECT_EQ(13, *(inteiro->busca(13, inteiro)));
    EXPECT_EQ(14, *(inteiro->busca(14, inteiro)));
    EXPECT_EQ(15, *(inteiro->busca(15, inteiro)));
    EXPECT_EQ(17, *(inteiro->busca(17, inteiro)));
    EXPECT_EQ(18, *(inteiro->busca(18, inteiro)));
    EXPECT_EQ(20, *(inteiro->busca(20, inteiro)));
}

TEST_F(NoAVLTest, removerRotacaoDuplaDireita) {
    inteiro = inteiro->inserir(4, inteiro);
    inteiro = inteiro->inserir(15, inteiro);
    inteiro = inteiro->inserir(14, inteiro);
    inteiro = inteiro->inserir(17, inteiro);
    inteiro = inteiro->inserir(6, inteiro);
    inteiro = inteiro->inserir(20, inteiro);
    inteiro = inteiro->inserir(13, inteiro);
    inteiro = inteiro->inserir(25, inteiro);
    inteiro = inteiro->inserir(7, inteiro);
    inteiro = inteiro->inserir(8, inteiro);
    inteiro = inteiro->inserir(2, inteiro);
    inteiro = inteiro->inserir(26, inteiro);
    inteiro = inteiro->inserir(16, inteiro);

    ASSERT_EQ(4, inteiro->getAltura());
    ASSERT_EQ(14, verifica_altura_recursivo(inteiro));

    inteiro = inteiro->remover(inteiro, 14);
    inteiro = inteiro->remover(inteiro, 13);
    // Rotação dupla à Direita
    ASSERT_EQ(3, inteiro->getAltura());
    ASSERT_EQ(12, verifica_altura_recursivo(inteiro));

    EXPECT_EQ(2, *(inteiro->busca(2, inteiro)));
    EXPECT_EQ(4, *(inteiro->busca(4, inteiro)));
    EXPECT_EQ(6, *(inteiro->busca(6, inteiro)));
    EXPECT_EQ(7, *(inteiro->busca(7, inteiro)));
    EXPECT_EQ(8, *(inteiro->busca(8, inteiro)));
    EXPECT_EQ(10, *(inteiro->busca(10, inteiro)));
    EXPECT_EQ(15, *(inteiro->busca(15, inteiro)));
    EXPECT_EQ(16, *(inteiro->busca(16, inteiro)));
    EXPECT_EQ(17, *(inteiro->busca(17, inteiro)));
    EXPECT_EQ(25, *(inteiro->busca(25, inteiro)));
    EXPECT_EQ(26, *(inteiro->busca(26, inteiro)));
}

TEST_F(NoAVLTest, minimo) {
    int h;
    ASSERT_EQ(INITVAL, *(inteiro->minimo(inteiro)->getDado()));
    for (h = INITVAL-1; h >= 0; h--) {
        inteiro = inteiro->inserir(h, inteiro);
        ASSERT_EQ(h, *(inteiro->minimo(inteiro)->getDado()));
    }
}

TEST_F(NoAVLTest, busca) {
    int h;
    for (h = 0; h < TAM1; h++) {
        if (h == INITVAL) continue;
        inteiro = inteiro->inserir(h, inteiro);
    }

    for (h = 0; h < TAM1; h++) {
        ASSERT_EQ(h, *(inteiro->busca(h, inteiro)));
    }

    for (h = TAM1+1; h < TAM2; h++) {
        ASSERT_ANY_THROW(inteiro->busca(h, inteiro));
    }
}


TEST_F(NoAVLTest, inserir100ElementosERemoverTodos) {
    int h;
    for (h = 0; h < TAM1; h++) {
        if (h == INITVAL) continue;
        inteiro = inteiro->inserir(h, inteiro);
    }

    for (h = 0; h < TAM1; h++) {
        ASSERT_EQ(h, *(inteiro->busca(h, inteiro)));
    }

    for (h = 0; h < TAM1; h++) {
        inteiro = inteiro->remover(inteiro, h);
    }

    for (h = 0; h < TAM1; h++) {
        ASSERT_ANY_THROW(inteiro->busca(h, inteiro));
    }
}

TEST_F(NoAVLTest, preOrdem) {
    inteiro = inteiro->inserir(INITVAL-2, inteiro);
    inteiro = inteiro->inserir(INITVAL-1, inteiro);
    inteiro = inteiro->inserir(INITVAL+1, inteiro);
    inteiro = inteiro->inserir(INITVAL+2, inteiro);

    inteiro->preOrdem(inteiro);
    std::vector<NoAVL<int>* > elementos = inteiro->getElementos();

    ASSERT_EQ(INITVAL-1, *(elementos[0]->getDado()));
    ASSERT_EQ(INITVAL-2, *(elementos[1]->getDado()));
    ASSERT_EQ(INITVAL+1, *(elementos[2]->getDado()));
    ASSERT_EQ(INITVAL, *(elementos[3]->getDado()));
    ASSERT_EQ(INITVAL+2, *(elementos[4]->getDado()));
}

TEST_F(NoAVLTest, emOrdem) {
    inteiro = inteiro->inserir(INITVAL-2, inteiro);
    inteiro = inteiro->inserir(INITVAL-1, inteiro);
    inteiro = inteiro->inserir(INITVAL+1, inteiro);
    inteiro = inteiro->inserir(INITVAL+2, inteiro);

    inteiro->emOrdem(inteiro);
    std::vector<NoAVL<int>* > elementos = inteiro->getElementos();

    ASSERT_EQ(INITVAL-2, *(elementos[0]->getDado()));
    ASSERT_EQ(INITVAL-1, *(elementos[1]->getDado()));
    ASSERT_EQ(INITVAL, *(elementos[2]->getDado()));
    ASSERT_EQ(INITVAL+1, *(elementos[3]->getDado()));
    ASSERT_EQ(INITVAL+2, *(elementos[4]->getDado()));
}

TEST_F(NoAVLTest, posOrdem) {
    inteiro = inteiro->inserir(INITVAL-2, inteiro);
    inteiro = inteiro->inserir(INITVAL-1, inteiro);
    inteiro = inteiro->inserir(INITVAL+1, inteiro);
    inteiro = inteiro->inserir(INITVAL+2, inteiro);

    inteiro->posOrdem(inteiro);
    std::vector<NoAVL<int>* > elementos = inteiro->getElementos();

    ASSERT_EQ(INITVAL-2, *(elementos[0]->getDado()));
    ASSERT_EQ(INITVAL, *(elementos[1]->getDado()));
    ASSERT_EQ(INITVAL+2, *(elementos[2]->getDado()));
    ASSERT_EQ(INITVAL+1, *(elementos[3]->getDado()));
    ASSERT_EQ(INITVAL-1, *(elementos[4]->getDado()));
}
