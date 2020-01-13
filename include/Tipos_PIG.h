/********************************
Tipos de dados mais utilizados pela PIG
versão da PIG compatível: 0.5.1
********************************/


/********************************
Principais definições utilizadas pela PIG
********************************/

#define ALT_TELA                768
#define LARG_TELA               1366
#define MAX_CURSORES            20
#define MAX_FONTES              100
#define PRIMEIRO_CAR            26
#define ULTIMO_CAR              256
#define NOME_ARQ_TEMP           "fontess.bmp"

#define MAX_SLOTS_AL            4000

#define MAX_ANIMACOES           1000
#define MAX_FRAMES              2000
#define MAX_FRAMES_MODO         100
#define MAX_MODOS               50

#define MAX_OBJETOS             20000
#define MAX_ATRIBUTOS_OBJETO    100

#define MAX_TIMERS              5000

#define MAX_GERADORPARTICULAS   100
#define MAX_PARTICULAS          1000

#define SHARE_BITMAP


/********************************
O tipo PIG_Cor é um struct formado por 4 campos: r,g,b,a correspondendo aos valores de vermelho, verde, azul e alfa (transparência) do pixel
********************************/
#define PIG_Cor         SDL_Color
#define BRANCO          ((PIG_Cor){255,255,255,255})
#define PRETO           ((PIG_Cor){0,0,0,255})
#define AZUL            ((PIG_Cor){0,0,255,255})
#define VERMELHO        ((PIG_Cor){255,0,0,255})
#define VERDE           ((PIG_Cor){0,255,0,255})
#define AMARELO         ((PIG_Cor){255,255,0,255})
#define ROSA            ((PIG_Cor){255,0,255,255})
#define ROXO            ((PIG_Cor){115,0,230,255})
#define LARANJA         ((PIG_Cor){255,128,0,255})
#define CIANO           ((PIG_Cor){0,255,255,255})
#define CINZA           ((PIG_Cor){128,128,128,255})
#define CINZA_ESCURO    ((PIG_Cor){64,64,64,255})
#define CINZA_CLARO     ((PIG_Cor){196,196,196,255})
#define CORESIGUAIS(x,y)(((PIG_Cor)x).r==((PIG_Cor)y).r && ((PIG_Cor)x).g==((PIG_Cor)y).g && ((PIG_Cor)x).b==((PIG_Cor)y).b)


/********************************
O PIG_TipoEvento é uma enumeração que contém os seguintes possíveis valores:
EVENTO_NULO: indica que não houve evento desde a última chamada da função Pega_Evento()
EVENTO_GERAL: (não implementado)
EVENTO_JANELA: indica algum possível evento relacionado à janela de jogo (redimensionamento, movimento, perda ou ganho de foco etc)
EVENTO_TECLADO: indica algum possível evento relacionado ao teclado do computador (tecla pressionada ou liberada, texto digitado ou editado etc)
EVENTO_MOUSE: indica algum possível evento relacionado ao mouse do compuatdor (botão pressionado ou liberado, movimentação, uso da rodinha etc)
EVENTO_AUDIO: (não implementado)
EVENTO_CONTROLADOR: (não implementado)
EVENTO_USUARIO: (não implementado)
********************************/
typedef enum PIG_TipoEvento{EVENTO_NULO,
                            EVENTO_GERAL,
                            EVENTO_JANELA,
                            EVENTO_TECLADO,
                            EVENTO_MOUSE,
                            EVENTO_AUDIO,
                            EVENTO_CONTROLADOR,
                            EVENTO_USUARIO}
                PIG_TipoEvento;

/********************************
O InfoEventoMouse é um struct contendo informações específicas sobre o evento de mouse:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
posX: a posição no eixo X do ponteiro do mouse no momento de ocorrência do evento
posY: a posição no eixo Y do ponteiro do mouse no momento de ocorrência do evento
botao: indica qual dos possíveis três botões foi pressionado ou liberado
relX: indica o deslocamento no eixo X quando há uma movimentação de mouse; adicionalmente, representa o deslocamento da rodinha no eixo X (não usado)
relX: indica o deslocamento no eixo Y quando há uma movimentação de mouse; adicionalmente, representa o deslocamento da rodinha no eixo Y
********************************/
typedef struct InfoEventoMouse{
    int acao;
    int posX,posY;
    int botao;
    int relX,relY;
}InfoEventoMouse;
#define MOUSE_PRESSIONADO       SDL_MOUSEBUTTONDOWN
#define MOUSE_LIBERADO          SDL_MOUSEBUTTONUP
#define MOUSE_MOVIDO            SDL_MOUSEMOTION
#define MOUSE_RODINHA           SDL_MOUSEWHEEL
#define MOUSE_DIREITO           SDL_BUTTON_RIGHT
#define MOUSE_ESQUERDO          SDL_BUTTON_LEFT
#define MOUSE_CENTRAL           SDL_BUTTON_MIDDLE

/********************************
O InfoEventoJanela é um struct contendo informações específicas sobre o evento de janela:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
dado1,dado2: indicam em conjunto a informação específica do evento, podendo representar o ponto (X,Y), em relação ao monitor,
para o qual a janela foi movida ou o novo tamanho da janela após um alteração de dimensões na mesma
********************************/
typedef struct InfoEventoJanela{
    int acao;
    int dado1,dado2;
}InfoEventoJanela;
#define JANELA_EXIBIDA          SDL_WINDOWEVENT_SHOWN
#define JANELA_OCULTA           SDL_WINDOWEVENT_HIDDEN
#define JANELA_EXPOSTA          SDL_WINDOWEVENT_EXPOSED
#define JANELA_MOVIDA           SDL_WINDOWEVENT_MOVED
#define JANELA_REDIMENSIONADA   SDL_WINDOWEVENT_RESIZED
#define JANELA_ALTERADA         SDL_WINDOWEVENT_SIZE_CHANGED
#define JANELA_MINIMIZADA       SDL_WINDOWEVENT_MINIMIZED
#define JANELA_MAXIMIZADA       SDL_WINDOWEVENT_MAXIMIZED
#define JANELA_RESTAURADA       SDL_WINDOWEVENT_RESTORED
#define JANELA_MOUSEDENTRO      SDL_WINDOWEVENT_ENTER
#define JANELA_MOUSEFORA        SDL_WINDOWEVENT_LEAVE
#define JANELA_GANHOFOCO        SDL_WINDOWEVENT_FOCUS_GAINED
#define JANELA_PERDAFOCO        SDL_WINDOWEVENT_FOCUS_LOST
#define JANELA_FECHADA          SDL_WINDOWEVENT_CLOSE

/********************************
O InfoEventoTeclado é um struct contendo informações específicas sobre o evento de teclado:
acao: código que representa o evento específico (os possíveis valores podem ser vistos abaixo do struct)
tecla: código que representa a tecla pressionada ou liberada. Os possíveis valores pdoem ser vistos nofinal deste arquivo.
repeticao: indica se está havendo repetição no acionamento desta tecla ou não
texto: indica o que está sendo inserido
inicio: indica a posição virtual da parte selecionada do texto a ser editado
tamanhoSelecao: indica o tamanho (quantidade de caracteres) da seleção do texto a ser editado
********************************/
typedef struct InfoEventoTeclado{
    int acao;
    int tecla;
    int repeticao;
    char texto[32];
    int inicio,tamanhoSelecao;
}InfoEventoTeclado;
#define TECLA_PRESSIONADA       SDL_KEYDOWN
#define TECLA_LIBERADA          SDL_KEYUP
#define TECLA_EDICAO            SDL_TEXTEDITING
#define TECLA_INPUT             SDL_TEXTINPUT

typedef struct PIG_Evento{
    PIG_TipoEvento tipoEvento;
    InfoEventoMouse mouse;
    InfoEventoJanela janela;
    InfoEventoTeclado teclado;
} PIG_Evento;


#define PIG_Teclado             const Uint8*

//Seção de flips de objetos

#define PIG_Flip                SDL_RendererFlip
#define FLIP_NENHUM             SDL_FLIP_NONE
#define FLIP_HORIZONTAL         SDL_FLIP_HORIZONTAL
#define FLIP_VERTICAL           SDL_FLIP_VERTICAL
#define FLIP_HORIZ_VERT         FLIP_HORIZONTAL|FLIP_VERTICAL

//Seção de estilos

#define PIG_Estilo              int
#define ESTILO_NORMAL           TTF_STYLE_NORMAL
#define ESTILO_NEGRITO          TTF_STYLE_BOLD
#define ESTILO_ITALICO          TTF_STYLE_ITALIC
#define ESTILO_SUBLINHADO       TTF_STYLE_UNDERLINE
#define ESTILO_CORTADO          TTF_STYLE_STRIKETHROUGH

//Seção de teclas

#define TECLA_UNKNOWN           0

#define TECLA_ENTER             SDL_SCANCODE_RETURN
#define TECLA_ESC               SDL_SCANCODE_ESCAPE
#define TECLA_BACKSPACE         SDL_SCANCODE_BACKSPACE
#define TECLA_TAB               SDL_SCANCODE_TAB
#define TECLA_BARRAESPACO       SDL_SCANCODE_SPACE
#define TECLA_EXCLAMACAO        SDL_SCANCODE_EXCLAIM
#define TECLA_ASPASDUPLAS       SDL_SCANCODE_QUOTEDBL
#define TECLA_HASH              SDL_SCANCODE_HASH
#define TECLA_PORCENTO          SDL_SCANCODE_PERCENT
#define TECLA_CIFRAO            SDL_SCANCODE_DOLLAR
#define TECLA_ECOMERCIAL        SDL_SCANCODE_AMPERSAND
#define TECLA_ASPASIMPLES       SDL_SCANCODE_QUOTE
#define TECLA_ABREPARENTESES    SDL_SCANCODE_LEFTPAREN
#define TECLA_FECHAPARENTESES   SDL_SCANCODE_RIGHTPAREN
#define TECLA_ASTERISCO         SDL_SCANCODE_ASTERISK
#define TECLA_MAIS              SDL_SCANCODE_PLUS
#define TECLA_VIRGULA           SDL_SCANCODE_COMMA
#define TECLA_MENOS             SDL_SCANCODE_MINUS
#define TECLA_PONTO             SDL_SCANCODE_PERIOD
#define TECLA_BARRA             SDL_SCANCODE_SLASH
#define TECLA_0                 SDL_SCANCODE_0
#define TECLA_1                 SDL_SCANCODE_1
#define TECLA_2                 SDL_SCANCODE_2
#define TECLA_3                 SDL_SCANCODE_3
#define TECLA_4                 SDL_SCANCODE_4
#define TECLA_5                 SDL_SCANCODE_5
#define TECLA_6                 SDL_SCANCODE_6
#define TECLA_7                 SDL_SCANCODE_7
#define TECLA_8                 SDL_SCANCODE_8
#define TECLA_9                 SDL_SCANCODE_9
#define TECLA_DOISPONTOS        SDL_SCANCODE_COLON
#define TECLA_PONTOEVIRGULA     SDL_SCANCODE_SEMICOLON
#define TECLA_MENORQUE          SDL_SCANCODE_LESS
#define TECLA_IGUAL             SDL_SCANCODE_EQUALS
#define TECLA_MAIORQUE          SDL_SCANCODE_GREATER
#define TECLA_INTERROGACAO      SDL_SCANCODE_QUESTION
#define TECLA_ARROBA            SDL_SCANCODE_AT

#define TECLA_ABRECOLCHETE      SDL_SCANCODE_LEFTBRACKET
#define TECLA_CONTRABARRA       SDL_SCANCODE_BACKSLASH
#define TECLA_FECHACOLCHETE     SDL_SCANCODE_RIGHTBRACKET
#define TECLA_CIRCUNFLEXO       SDL_SCANCODE_CARET
#define TECLA_TRAVESSAO         SDL_SCANCODE_UNDERSCORE
#define TECLA_GRAVE             SDL_SCANCODE_BACKQUOTE
#define TECLA_a                 SDL_SCANCODE_A
#define TECLA_b                 SDL_SCANCODE_B
#define TECLA_c                 SDL_SCANCODE_C
#define TECLA_d                 SDL_SCANCODE_D
#define TECLA_e                 SDL_SCANCODE_E
#define TECLA_f                 SDL_SCANCODE_F
#define TECLA_g                 SDL_SCANCODE_G
#define TECLA_h                 SDL_SCANCODE_H
#define TECLA_i                 SDL_SCANCODE_I
#define TECLA_j                 SDL_SCANCODE_J
#define TECLA_k                 SDL_SCANCODE_K
#define TECLA_l                 SDL_SCANCODE_L
#define TECLA_m                 SDL_SCANCODE_M
#define TECLA_n                 SDL_SCANCODE_N
#define TECLA_o                 SDL_SCANCODE_O
#define TECLA_p                 SDL_SCANCODE_P
#define TECLA_q                 SDL_SCANCODE_Q
#define TECLA_r                 SDL_SCANCODE_R
#define TECLA_s                 SDL_SCANCODE_S
#define TECLA_t                 SDL_SCANCODE_T
#define TECLA_u                 SDL_SCANCODE_U
#define TECLA_v                 SDL_SCANCODE_V
#define TECLA_w                 SDL_SCANCODE_W
#define TECLA_x                 SDL_SCANCODE_X
#define TECLA_y                 SDL_SCANCODE_Y
#define TECLA_z                 SDL_SCANCODE_Z

#define TECLA_CAPSLOCK          SDL_SCANCODE_CAPSLOCK

#define TECLA_F1                SDL_SCANCODE_F1
#define TECLA_F2                SDL_SCANCODE_F2
#define TECLA_F3                SDL_SCANCODE_F3
#define TECLA_F4                SDL_SCANCODE_F4
#define TECLA_F5                SDL_SCANCODE_F5
#define TECLA_F6                SDL_SCANCODE_F6
#define TECLA_F7                SDL_SCANCODE_F7
#define TECLA_F8                SDL_SCANCODE_F8
#define TECLA_F9                SDL_SCANCODE_F9
#define TECLA_F10               SDL_SCANCODE_F10
#define TECLA_F11               SDL_SCANCODE_F11
#define TECLA_F12               SDL_SCANCODE_F12

#define TECLA_PRINTSCREEN       SDL_SCANCODE_PRINTSCREEN
#define TECLA_SCROLLLOCK        SDL_SCANCODE_SCROLLLOCK
#define TECLA_PAUSE             SDL_SCANCODE_PAUSE
#define TECLA_INSERT            SDL_SCANCODE_INSERT
#define TECLA_HOME              SDL_SCANCODE_HOME
#define TECLA_PAGEUP            SDL_SCANCODE_PAGEUP
#define TECLA_DELETE            SDL_SCANCODE_DELETE
#define TECLA_END               SDL_SCANCODE_END
#define TECLA_PAGEDOWN          SDL_SCANCODE_PAGEDOWN
#define TECLA_DIREITA           SDL_SCANCODE_RIGHT
#define TECLA_ESQUERDA          SDL_SCANCODE_LEFT
#define TECLA_BAIXO             SDL_SCANCODE_DOWN
#define TECLA_CIMA              SDL_SCANCODE_UP

#define TECLA_NUMLOCKCLEAR      SDL_SCANCODE_NUMLOCKCLEAR
#define TECLA_KP_DIVISAO        SDL_SCANCODE_KP_DIVIDE
#define TECLA_KP_MULTIPLICAO    SDL_SCANCODE_KP_MULTIPLY
#define TECLA_KP_MENOS          SDL_SCANCODE_KP_MINUS
#define TECLA_KP_MAIS           SDL_SCANCODE_KP_PLUS
#define TECLA_KP_ENTER          SDL_SCANCODE_KP_ENTER
#define TECLA_KP_1              SDL_SCANCODE_KP_1
#define TECLA_KP_2              SDL_SCANCODE_KP_2
#define TECLA_KP_3              SDL_SCANCODE_KP_3
#define TECLA_KP_4              SDL_SCANCODE_KP_4
#define TECLA_KP_5              SDL_SCANCODE_KP_5
#define TECLA_KP_6              SDL_SCANCODE_KP_6
#define TECLA_KP_7              SDL_SCANCODE_KP_7
#define TECLA_KP_8              SDL_SCANCODE_KP_8
#define TECLA_KP_9              SDL_SCANCODE_KP_9
#define TECLA_KP_0              SDL_SCANCODE_KP_0
#define TECLA_KP_PONTO          SDL_SCANCODE_KP_PERIOD

#define TECLA_APPLICATION       SDL_SCANCODE_APPLICATION
#define TECLA_POWER             SDL_SCANCODE_POWER
#define TECLA_KP_IGUAL          SDL_SCANCODE_KP_EQUALS
#define TECLA_KP_VIRGULA        SDL_SCANCODE_KP_COMMA

#define TECLA_KP_MEMADD         SDL_SCANCODE_KP_MEMADD
#define TECLA_KP_MEMSUBTRACT    SDL_SCANCODE_KP_MEMSUBTRACT
#define TECLA_KP_MEMMULTIPLY    SDL_SCANCODE_KP_MEMMULTIPLY
#define TECLA_KP_MEMDIVIDE      SDL_SCANCODE_KP_MEMDIVIDE
#define TECLA_KP_PLUSMINUS      SDL_SCANCODE_KP_PLUSMINUS

#define TECLA_CTRLESQUERDO      SDL_SCANCODE_LCTRL
#define TECLA_SHIFTESQUERDO     SDL_SCANCODE_LSHIFT
#define TECLA_ALTESQUERDO       SDL_SCANCODE_LALT
#define TECLA_LGUI              SDL_SCANCODE_LGUI
#define TECLA_CTRLDIREITO       SDL_SCANCODE_RCTRL
#define TECLA_SHIFTDIREITO      SDL_SCANCODE_RSHIFT
#define TECLA_ALTDIREITO        SDL_SCANCODE_RALT
#define TECLA_RGUI              SDL_SCANCODE_RGUI
