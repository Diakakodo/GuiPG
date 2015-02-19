% univ-doc.cls
% Cette classe latex doit soit se trouver dans le repertoire
% courant ainsi que le logo soit être dans votre path latex
\ProvidesClass{CR-projet}

% Utilisation de la classe article comme base
\LoadClass[11pt]{article}

% utilisation des convention française
\usepackage[utf8x]{inputenc}
\usepackage[francais]{babel}

%Macro outil, ne devrait pas être utiliser en dehors de ce fichier.
\def\addtomacro#1#2{\edef#1{\unexpanded\expandafter{#1#2}}}

% champs supplmentaires pour la page de garde:
% projet, filiere, version, relecteur et logo.
% Ma command \presentry{Nom}{Prenom}{Présence}{couleur}
% permet d'ajouter des entrees aux tableau de présence de la page de garde.
\makeatletter
    \newcommand{\projet}[1]{\def \@projet {#1}}
    \newcommand{\projdesc}[1]{\def \@projdesc {#1}}
    \newcommand{\filiere}[1]{\def \@filiere {#1}}
    \newcommand{\matiere}[1]{\def \@matiere {#1}}
    \newcommand{\version}[1]{\def \@version {#1}}
    \newcommand{\relecteur}[1]{\def \@relecteur {#1}}
    \newcommand{\signataire}[1]{\def \@signataire {#1}}
    \newcommand{\logo}[1]{\def \@logo {#1}}
    \newcommand{\context}[1]{\def \@context {#1}}
    \newcommand{\presentry}[4]{\addtomacro{\@present}{#1&#2&\textcolor{#4}{#3}\\\hline}}
    \projet{}
    \filiere{}
    \version{}
    \relecteur{}
    \logo{}
    \signataire{}
    \projdesc{}
    \context{}
    \def \@present {} % Initialise le tableau de présence a vide.
\makeatother

% marges
\usepackage[top=1in,bottom=1in,left=1in,right=1in]{geometry}

% indentations
\usepackage{indentfirst}
\setlength{\parindent}{18pt}
\setlength{\parskip}{3pt}

% espacements
\usepackage{setspace}

% gestion des references
\usepackage{varioref}
\usepackage{hyperref}
\hypersetup{      % Configuration du style des liens.
  filecolor=cyan, % couleur des liens vers un fichier.
  urlcolor=blue,  % couleur des liens vers une url.
  linkcolor=black,% couleur des liens interne (Table of content).
  colorlinks=true % affichage des couleurs et non du cadre par default.
}

% gestion des figures
\usepackage{graphicx}

% gestion des couleurs
\usepackage[table]{xcolor}

% gestion bibliography
\usepackage{natbib}

% gestion de la dernière page
\usepackage{lastpage}

% entête et pagination
\makeatletter
    \usepackage{fancyhdr}
    \pagestyle{fancy}
    \setlength{\headheight}{35pt}
    \renewcommand{\footrulewidth}{\headrulewidth}
    \fancyhf{}

    \fancyhead[L]{\@filiere - \@matiere\\\@projet\\\@title}
    \fancyhead[R]{
      \ifx \@logo \@empty
      \else
      \includegraphics[width=0.20\textwidth]{\@logo}
      \fi      
    }

    \fancyfoot[R]{\thepage / \pageref{LastPage}}
\makeatother

% Permet de conditionner la mise en page de la page de garde.
\usepackage{ifthen}

%Macro commande pour la création d'un tableau de type fiche
\newcommand{\fiche}[9] {
	\noindent
\begin{tabular}{|p{3.5cm}| p{1cm} | p{3cm} | p{.5cm} | p{7cm}|} 
\hline
\multicolumn{2}{|>{\color{white}\columncolor{blue}}l|}{\bfseries{ Nom}} & \multicolumn{3}{>{\color{white}\columncolor{blue}}l|}{\bfseries{#1}}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Acteurs concernés}}} & \multicolumn{3}{m{10.5cm}|}{#2}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Description}}} & \multicolumn{3}{m{10.5cm}|}{#3}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Préconditions}}} & \multicolumn{3}{m{10.5cm}|}{#4}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Evénements déclenchants}}} & \multicolumn{3}{m{10.5cm}|}{#5}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Conditions d'arrêt}}} & \multicolumn{3}{m{10.5cm}|}{#6}\\
\hline
\multicolumn{5}{|>{\columncolor[gray]{.7}}l|}{\bfseries{\bfseries{Description du flot d'événements principal:}}}\\
\hline
\multicolumn{3}{|>{\columncolor[gray]{.7}}c|}{\bfseries{\bfseries{Acteur(s)}}} & \multicolumn{2}{>{\columncolor[gray]{.7}}c|}{\bfseries{\bfseries{Système}}}\\
\hline
\multicolumn{3}{|p{7.5cm}|}{#7} & \multicolumn{2}{p{7.5cm}|}{#8}\\
\hline
\bfseries{Flots d'exceptions:} & \multicolumn{4}{|p{11.5cm}|}{#9}\\
\hline
\end{tabular}
\\
}


% Mecanique de fiche avec une image pour la partie
% Description du flot d ’événements principal.
\newcommand{\ficheGraphic}[9] {
	\noindent
\begin{tabular}{|p{3.5cm}| p{1cm} | p{3cm} | p{.5cm} | p{7cm}|} 
\hline
\multicolumn{2}{|>{\color{white}\columncolor{blue}}l|}{\bfseries{ }} & \multicolumn{3}{>{\color{white}\columncolor{blue}}l|}{\bfseries{#1}}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Acteurs concern\'{e}s}}} & \multicolumn{3}{m{10.5cm}|}{#2}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Description}}} & \multicolumn{3}{m{10.5cm}|}{#3}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Pr\'{e}conditions}}} & \multicolumn{3}{m{10.5cm}|}{#4}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Ev\`{e}nements d\'{e}clenchants}}} & \multicolumn{3}{m{10.5cm}|}{#5}\\
\hline
\multicolumn{2}{|l|}{\bfseries{\bfseries{Conditions d'arr\^{e}t}}} & \multicolumn{3}{m{10.5cm}|}{#6}\\
\hline
\multicolumn{5}{|>{\columncolor[gray]{.7}}l|}{\bfseries{\bfseries{Description du flot d'\'{e}v\`{e}nements principal:}}}\\
\hline
\multicolumn{5}{|c|}{}\\
\multicolumn{5}{|c|}{\bfseries{\bfseries{\includegraphics[scale=#7]{#8}}}}\\
\hline
\bfseries{Flots d'exceptions:} & \multicolumn{4}{|p{11.5cm}|}{#9}\\
\hline
\end{tabular}
\\
}

% page de garde
\makeatletter
\def \maketitle{%
    \begin{titlepage}
	\ifx \@projet \@empty
            \relax
        \else
            \ifx \@projdesc \@empty
            \parbox[b][4em][b]{0.66\textwidth}{
                    \flushleft
                    {\Huge {\bfseries \@projet}}
                }
            \else
                \parbox[b][4em][b]{0.66\textwidth}{
                    \flushleft
                    {\Huge {\bfseries \@projet}}
                    \newline {\Large \@projdesc} 
                }
            \fi
        \fi
        \ifx \@logo \@empty
            \hfill
        \else
            \includegraphics[width=0.33\textwidth]{\@logo}
        \fi
        
        ~\vfill
        \begin{center}
            \ifx \@title \@empty
                \relax
            \else
                {\huge \textbf{\@title} {\Large \@version}}\\
            \fi
            {\@date}\\
            \vspace{2em}
            \ifx \@context \@empty
                \relax
            \else
                \Large Contexte: \@context\\
            \fi
            \ifx \@author \@empty
                \relax
            \else
                Auteur(s): \@author\\
            \fi
            \ifx \@relecteur \@empty
                \relax
            \else
                Relecteur(s): \@relecteur\\
            \fi
            \ifx \@signataire \@empty    
                \relax
            \else
                Approuv\'e par: \@signataire\\
            \fi
            \vspace{5em}
            \ifx \@present \@empty
                \relax
            \else
                \begin{tabular}[t]{|p{5cm}|p{5cm}|c|}
                    \hline
                    \rowcolor{gray} \textcolor{white} {\bfseries Nom} & \textcolor{white} {\bfseries Prénom} & \textcolor{white} {\bfseries Présence} \\
                    \hline
                    \@present
                \end{tabular}
            \fi
        \end{center}
        \vfill
    \end{titlepage}
}
\makeatother
