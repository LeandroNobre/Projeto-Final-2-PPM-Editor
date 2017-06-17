#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define max 512
#define STRMAX 51


using namespace std;


struct IMG
{
    int Pxl_max;
    int num_colunas;
    int num_linhas;
    int R[max][max];
    int G[max][max];
    int B[max][max];
};

bool verificar_limites(IMG img, int li,int ci, int lf, int cf){
int a,b;
a = img.num_linhas;
b = img.num_colunas;

if(li >= 0 && li < a && ci >= 0 && ci < b && lf > li && lf < a && cf > ci && cf < b ){
    return true;
}

return false;
}

void limpar(IMG& img)
{
    int i, j;
    img.Pxl_max = 255;
    img.num_colunas = 0;
    img.num_linhas = 0;
    for(i=0; i<max; i++)
    {
        for(j=0; j<max; j++)
        {
            img.R[i][j] = 0;
            img.G[i][j] = 0;
            img.B[i][j] = 0;

        }
    }

}

void computa_derivada_vertical(IMG img,IMG& img2)
{
    int i,j;
    float a,b,c;
    IMG aux;
    limpar(img2);
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = img.num_colunas;
    img2.num_linhas = img.num_linhas;

    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            aux.R[i][j] = img.R[i][j];
            aux.G[i][j] = img.G[i][j];
            aux.B[i][j] = img.B[i][j];
            // Eu sei que não precisa, mas é porque eu tive receio de alterar o arquivo original.

        }
    }

    for(i=1; i<img.num_linhas-1; i++)
    {
        for(j=1; j<img.num_colunas-1; j++)
        {
            c = (-0.25)*aux.B[i-1][j-1]  + 0*aux.B[i-1][j]  +  (0.25)*aux.B[i-1][j+1] + (-0.5)*aux.B[i][j-1]  + 0*aux.B[i][j]  +  (0.5)*aux.B[i][j+1] + (-0.25)*aux.B[i+1][j-1]  + 0*aux.B[i+1][j]  +  (0.25)*aux.B[i+1][j+1];
            b = (-0.25)*aux.G[i-1][j-1]  + 0*aux.G[i-1][j]  +  (0.25)*aux.G[i-1][j+1] + (-0.5)*aux.G[i][j-1]  + 0*aux.G[i][j]  +  (0.5)*aux.G[i][j+1] + (-0.25)*aux.G[i+1][j-1]  + 0*aux.G[i+1][j]  +  (0.25)*aux.G[i+1][j+1];
            a = (-0.25)*aux.R[i-1][j-1]  + 0*aux.R[i-1][j]  +  (0.25)*aux.R[i-1][j+1] + (-0.5)*aux.R[i][j-1]  + 0*aux.R[i][j]  +  (0.5)*aux.R[i][j+1] + (-0.25)*aux.R[i+1][j-1]  + 0*aux.R[i+1][j]  +  (0.25)*aux.R[i+1][j+1];
            if(a >= 0)
            {
                img2.R[i][j] = a;
            }
            else
            {
                img2.R[i][j] = -a;
            }

            if(b >= 0)
            {
                img2.G[i][j] = b;
            }
            else
            {
                img2.G[i][j] = -b;
            }

            if(c >= 0)
            {
                img2.B[i][j] = c;
            }
            else
            {
                img2.B[i][j] = -c;
            }
        }

    }

}

void diminui_tamanho(IMG img,IMG& img2)
{
    IMG aux;
    int i,j,k=0,p=0;
    limpar(img2);


    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            aux.R[i][j] = img.R[i][j];
            aux.G[i][j] = img.G[i][j];
            aux.B[i][j] = img.B[i][j];       // Eu sei que não precisa, mas é porque eu tive receio de alterar o arquivo original.

        }
    }
    for(i=0; i<img.num_linhas/2; i++)
    {
        p=0;
        for(j=0; j<img.num_colunas/2; j++)
        {

            img2.R[k][p] = aux.R[2*i][2*j];
            img2.G[k][p] = aux.G[2*i][2*j];
            img2.B[k][p] = aux.B[2*i][2*j];
            p++;
        }
        k++;

    }
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = img.num_colunas/2;
    img2.num_linhas = img.num_linhas/2;
}

void info_image(IMG& img)
{
    cout<<endl<<"Informacoes da imagem:"<<endl<<"Numero de linhas: "<<img.num_linhas<<endl<<"Numero de colunas: "<<img.num_colunas<<endl<<endl;
}

void corta_rgb(IMG img,IMG& img2,int li,int ci,int lf,int cf)
{
    IMG aux;
    int i,j,k=0,p=0;

    limpar(img2);
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = cf-ci;
    img2.num_linhas = lf-li;

    for(i=li; i<lf; i++)
    {
        for(j=ci; j<cf; j++)
        {

            aux.R[k][p] = img.R[i][j];
            aux.G[k][p] = img.G[i][j];
            aux.B[k][p] = img.B[i][j];

            p++;
        }
        p=0;
        k++;
    }

    for(i=0; i<lf-li; i++)
    {
        for(j=0; j<cf-ci; j++)
        {
            img2.R[i][j] = aux.R[i][j];
            img2.G[i][j] = aux.G[i][j];
            img2.B[i][j] = aux.B[i][j];
        }
    }

}

void inverte(IMG img,IMG& img2)
{
    IMG aux;
    int i,j;
    limpar(img2);
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = img.num_colunas;
    img2.num_linhas = img.num_linhas;

    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            aux.R[i][j] = img.R[i][j];
            aux.G[i][j] = img.G[i][j];
            aux.B[i][j] = img.B[i][j];       // Eu sei que não precisa, mas é porque eu tive receio de alterar o arquivo original.

        }
    }

    for(i=0; i<img.num_linhas; i++)
    {
        for (j=0; j<img.num_colunas; j++)
        {
            img2.R[i][img.num_colunas-j-1] = aux.R[i][j];
            img2.G[i][img.num_colunas-j-1] = aux.G[i][j];
            img2.B[i][img.num_colunas-j-1] = aux.B[i][j];
        }
    }

}

void abre_img(char nomediretorio[], IMG& img)
{
    int i,j;
    char test[3],test2[3];
    test2[0] = 'P';
    test2[1] = '3';
    test2[2] = '\0';

    ifstream photo;
    photo.open(nomediretorio);
    if(!(photo.is_open()))
    {
        cout<<"\nImagem nao pode ser carregada.";
        exit(0);
    }

    for(int k=0; k<2; k++)
    {
        photo>>test[k];

    }
    test[2] = '\0';

    if(strcmp(test,test2) != 0)
    {

        cout<<"\nArquivo não é do tipo ppm(P3)";
        exit(0);
    }


    photo>> img.num_colunas >> img.num_linhas;
    if(img.num_colunas > 512 || img.num_linhas > 512 || img.num_colunas <= 0 || img.num_linhas <= 0 ){
        cout<<"\nTamanho inválido. Tamanho suportado]0,512]/]0,512]";
        exit(0);
        }

    photo>> img.Pxl_max;


    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            photo>> img.R[i][j] >> img.G[i][j] >> img.B[i][j];
        }

    }

    cout<<endl<<"\nImagem carregada com sucesso."<<endl;
}

void salva_img(char nomediretorio[], IMG& img)
{
    ofstream outfile(nomediretorio);
    int j,i;
    /*save.open(nomediretorio);
    if(!(save.is_open()))
    {                                  Descartei, pois sobrescrevia um arquivo fixo de save.
        cout<<"Diretorio invalido";
        exit(0);

    }*/
    outfile<<"P3"<<endl<<img.num_colunas<<" "<<img.num_linhas<<endl<<img.Pxl_max<<endl;
    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            outfile<<img.R[i][j]<<" "<<img.G[i][j]<<" "<<img.B[i][j]<<" ";
        }
        outfile<<endl;
    }

    outfile.close();

    cout<<"\nImagem salva com sucesso."<<endl;
}

void rotaciona(IMG img, IMG& img2)
{
    IMG auxiliar;
    int i,j;
    limpar(img2);
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = img.num_linhas;
    img2.num_linhas = img.num_colunas;

    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            auxiliar.R[i][j] = img.R[i][j];
            auxiliar.G[i][j] = img.G[i][j];
            auxiliar.B[i][j] = img.B[i][j];

        }
    }

    for(i=0; i<img.num_linhas; i++)
    {
        for(j=0; j<img.num_colunas; j++)
        {
            img2.R[img.num_colunas-j-1][i] = auxiliar.R[i][j];
            img2.G[img.num_colunas-j-1][i] = auxiliar.G[i][j];
            img2.B[img.num_colunas-j-1][i] = auxiliar.B[i][j];

        }
    }


}

void converte_para_cinza(IMG img, IMG& img2)
{
    int i,j;
    limpar(img2);
    img2.Pxl_max = img.Pxl_max;
    img2.num_colunas = img.num_colunas;
    img2.num_linhas = img.num_linhas;

    for(i=0; i<img.num_linhas; i++)
    {
        for (j=0; j<img.num_colunas; j++)
        {
            int med = 0;
            med = (img.R[i][j] + img.G[i][j] + img.B[i][j])/3;  // Computa a média entre os três níveis.

            img2.R[i][j] = med;
            img2.G[i][j] = med;
            img2.B[i][j] = med;
        }
    }


}

int main (void)
{

    int acao = -1;
    char diretorio1[STRMAX],diretorio2[STRMAX];/*O 1 é para chamar e 2 para salvar*/
    IMG img,img2;
    while(acao != 0)
    {
        cout<<"\t####################################################";
        cout<<endl<<"\t###No programa há cinco opcoes de acoes de edicao###\n"<<"\t####################################################\n"<<endl<<"\tRotacionar imagem no sentido anti-horario <Digite 1>"
            <<endl<<"\tInversao horizontal <Digite 2>"<<endl<<"\tRedução de tamanho <Digite 3>"<<endl<<"\tFiltragem passa altas <Digite 4>"<<endl<<
            "\tConversao para niveis de cinza <Digite 5>"<<endl<<"\tCorte de imagem <Digite 6>\n"<<endl<<"\tSair <Digite 7>"<<endl;
        cout<<endl<<"\tInforme a acão desejada: ";
        cin>>acao;

        if(acao == 7 )
            exit(0);

        cout<<"\tInsira o nome do arquivo a ser verificado: ";
        cin>>diretorio1;
        abre_img(diretorio1,img);
        info_image(img);


        if(acao == 1)
        {
            rotaciona(img,img2);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);

        }

        if(acao == 2)
        {

            inverte(img,img2);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);

        }

        if(acao == 3)
        {
            diminui_tamanho(img,img2);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);
        }

        if(acao == 4)
        {

            computa_derivada_vertical(img,img2);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);
        }

        if(acao == 5)
        {

            converte_para_cinza(img,img2);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);
        }

        if(acao == 6)
        {
            int li,ci,lf,cf;
            cout<<"\tInsira o par (linha e coluna) iniciais juntamente com o par (linha e coluna) finais: ";
            cin>>li>>ci>>lf>>cf;
            if(verificar_limites(img,li,ci,lf,cf) == true){
            corta_rgb(img,img2,li,ci,lf,cf);
            cout<<endl<<endl<<"\tDigite o nome do arquivo para salvar o projeto: ";
            cin>>diretorio2;
            salva_img(diretorio2,img2);
            limpar(img2);}
            else{
            cout<<"\tLimites Invalidos"<<endl;}
        }

        cout<<endl<<"\tPara sair, aperte zero, mas se quiser continuar, digite qualquer outro numero. "<<endl;
        cin>>acao;
        if(acao == 0){
            exit(0);
        }
        system("CLS");
    }
    return 0;

}




