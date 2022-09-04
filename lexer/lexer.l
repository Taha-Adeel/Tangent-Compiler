%{

%}

%%

%%

int main(int argc, char* argv[]){
        if(argc != 1)return -1; //number of input args
        yyin = fopen(argv[1], "r");
        yylex();
        fclose(yyin);
        return 0;
}