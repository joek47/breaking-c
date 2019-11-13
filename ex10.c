#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Please enter more arguments.\n");
        return 1;
    }

    int TO_LOWER_CASE = 97 - 65;
    int i;
    int j;
    char letter;

    for(j = 1; j < argc;  j++){ // handle all arguments
        printf("Argument %d:\n", j);

        for (i = 0; argv[j][i] != '\0', letter = argv[j][i] ; i++){

            // char letter = argv[1][i];
            if (letter <= 90 && letter >= 65 ){
                letter += TO_LOWER_CASE;    // character is just an integer
            }

            switch (letter){
                case 'a':
                // case 'A':
                    printf("%d: %c is a vowel.\n", i, letter);
                    break;

                case 'e':
                // case 'E':
                    printf("%d: %c is a vowel.\n", i, letter);
                    break;

                case 'i':
                // case 'I':
                    printf("%d: %c is a vowel.\n", i, letter);
                    break;

                case 'o':
                // case 'O':
                    printf("%d: %c is a vowel.\n", i, letter);
                    break;

                case 'u':
                // case 'U':
                    printf("%d: %c is a vowel.\n", i, letter);
                    break;
                case 'y':
                    if (i > 2){
                        printf("%d: %c.\n", i, letter);
                        // break;
                    }
                    break;

                default:
                    printf("%d: %c is not a vowel.\n", i, letter);
            }
        }
    } 
}
