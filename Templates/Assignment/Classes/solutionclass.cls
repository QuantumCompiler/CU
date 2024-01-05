%---------------------------------------------------------------------------
%	FORMAT AND CLASS
%---------------------------------------------------------------------------
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{solutionclass}[]
\LoadClass[a4paper, twoside, 10pt]{book}
\newcommand{\authorName}{Student Name}
\newcommand{\classCode}{Course Code}
\newcommand{\className}{Course Name}
\newcommand{\documentName}{Assignment Name}
\newcommand{\documentNumber}{Assignment Number}
\newcommand{\universityName}{University Of Colorado}
%---------------------------------------------------------------------------
%	LANGUAGE AND ENCODING
%---------------------------------------------------------------------------
\RequirePackage[portuguese, english]{babel} % Allows to use multiple languages in the document
\RequirePackage[utf8]{inputenc} % Defines the input encoding
\RequirePackage[T1]{fontenc} % Defines the font encoding
%---------------------------------------------------------------------------
%	TEXT FORMATTING AND MANIPULATION
%---------------------------------------------------------------------------
\RequirePackage{indentfirst} % Indent the first paragraph of a section
\RequirePackage{datetime} % Provides various features of date and time formatting
\RequirePackage{csquotes} % Context sensitive quotation facilities
\RequirePackage{mathrsfs} % Provides additional math scripts fonts
\RequirePackage{titlesec} % Allows customization of section titles
\RequirePackage{upgreek} % Provides upright greek letters
\RequirePackage{dsfont} % Provides various math symbols such as the indicator function
\RequirePackage{pifont} % Provides various symbols such as check marks and crosses
\RequirePackage{lipsum} % Generates Lorem Ipsum text for testing purposes
%---------------------------------------------------------------------------
%	MATHEMATICS AND PHYSICS
%---------------------------------------------------------------------------
\RequirePackage{amsmath} % for mathematical symbols
\RequirePackage{amssymb} % for mathematical symbols
\RequirePackage{mathtools} % for mathematical typesetting
% \RequirePackage{physics} % for mathematical physics
\RequirePackage{stmaryrd} % for mathematical symbols
\RequirePackage{tensor} % for tensors
\RequirePackage{calc} % for mathematical calculations
\RequirePackage{listings} % for code listing
\RequirePackage{cancel} % 
\renewcommand{\theequation}{\arabic{equation}}
%---------------------------------------------------------------------------
%	CODE ANNOTATIONS
%---------------------------------------------------------------------------
\lstdefinestyle{stackoverflow}{
    backgroundcolor=\color[rgb]{0.95, 0.95, 0.95},
    basicstyle=\ttfamily\scriptsize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    commentstyle=\color[rgb]{0.0, 0.5, 0.0},
    frame=single,
    keepspaces=true,
    keywordstyle=\color[rgb]{0.0, 0.0, 1.0},
    numbers=left,
    numbersep=-5pt,
    numberstyle=\tiny\color[rgb]{0.5, 0.5, 0.5},
    rulecolor=\color[rgb]{0.0, 0.0, 0.0},
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    stringstyle=\color[rgb]{1.0, 0.0, 0.0},
    tabsize=4,
}
%---------------------------------------------------------------------------
%	FIGURES, TIKZ AND BOXES
%---------------------------------------------------------------------------
\RequirePackage{graphicx} % for including images
\RequirePackage{float} % provides H option for figures and tables
\RequirePackage{xcolor} % for color support
\RequirePackage{tikz} % for creating graphics and diagrams
\RequirePackage{tikz-3dplot} % for 3D graphics in TikZ
\RequirePackage{pgfplots} % for creating plots and diagrams
\RequirePackage[most,breakable]{tcolorbox} % for creating colored boxes and frames
%---------------------------------------------------------------------------
%	PAGE AND TEXT STYLES
%---------------------------------------------------------------------------
\RequirePackage[colorlinks = true,
                urlcolor = LinkColor,
                anchorcolor = LinkColor,
                citecolor = LinkColor,
                filecolor = LinkColor,
                linkcolor = LinkColor,
                menucolor = LinkColor,
                linktocpage = true,
                bookmarks = true,
                pdfusetitle]{hyperref} % Hyperlinks
\RequirePackage[top = 2cm,
                bottom = 2cm,
                left = 1.75cm,
                right = 1.75cm,
                ]{geometry} % Page margins
\RequirePackage[shortlabels]{enumitem} % Customized lists
\RequirePackage{microtype} % Improves typography
\RequirePackage{fancyhdr} % Custom headers and footers
\RequirePackage{titletoc} % Custom table of contents
\RequirePackage{lastpage} % Reference to the last page
\RequirePackage{etoolbox} % Toolbox of programming tools
\RequirePackage{multicol} % Multiple columns
\RequirePackage{caption} % Customizing captions
\RequirePackage{lmodern} % Latin Modern fonts
\RequirePackage{nameref} % Cross-referencing by name
\RequirePackage{changepage} % Change page dimensions
\RequirePackage{background} % Background image
\RequirePackage{hyperref} % Hyperref package
\RequirePackage{pdfpages} % Embed a pdf page
\RequirePackage{mdframed} % Boxes
%---------------------------------------------------------------------------
%	HEADER AND FOOTER
%---------------------------------------------------------------------------
\pagestyle{fancy}
\fancyhead[L]{\footnotesize{\authorName}}
\fancyfoot[L]{\footnotesize{\classCode}}
\fancyhead[C]{\footnotesize{\className}}
\fancyhead[R]{\footnotesize{\universityName}}
\fancyfoot[R]{\footnotesize{\documentName}}
%---------------------------------------------------------------------------
%	BACKGROUND
%---------------------------------------------------------------------------
\backgroundsetup{
    scale = 1,
    angle = 0,
    opacity = 0.1,
    contents = {
    \includegraphics[scale = 0.25, keepaspectratio]{./Figures/CU Seal.png}
    }
}
%---------------------------------------------------------------------------
%	TIKZ SETTINGS
%---------------------------------------------------------------------------
\usetikzlibrary{%
    decorations.pathreplacing, % Create decorative path elements that replace parts of the original path.
    decorations.pathmorphing, % Create decorative path elements that morph the original path.
    decorations.markings, % Place decorations along a path.
    shapes.multipart, % Create nodes with multiple parts.
    shapes.geometric, % Provide additional geometric shapes.
    arrows.meta, % Define arrowheads for paths.
    tikzmark, % Place markers on a path or in a TikZ picture.
    fadings, % Create gradient and transparency effects.
    arrows, % Provide additional arrowheads.
    angles, % Measure and display angles between lines.
    quotes, % Place quotes on a path.
    calc, % Provide additional mathematical functions.
    3d, % Create three-dimensional TikZ diagrams.
}
\pgfplotsset{compat=1.18} % Sets the compatibility level for the pgfplots package to version 1.18, ensuring consistent compilation of plots and diagrams in the document.

\tikzset{>=stealth} % Arrow style for all tikZ environment.
%---------------------------------------------------------------------------
%	COLOR SETTINGS
%---------------------------------------------------------------------------
% To change the darker color of the document, like the cover page background, change the hexadecimal code #101010 to the color which you want. To know what hexadecimal code you need, access https://htmlcolorcodes.com
\definecolor{myDColor}{HTML}{000000} % Darker Color
% To change the lighter color of the document, like the box solution backaground, change the hexadecimal code #e93820 to the color which you want
\definecolor{myLColor}{HTML}{CFB87C} % Lighter Color
% To change the link color of the document, like the mentions, change the hexadecimal code #eb5a00 to the color which you want
\definecolor{LinkColor}{HTML}{CFB87C} % Link Color
%---------------------------------------------------------------------------
%	CHAPTER AND SECTION SETTINGS
%---------------------------------------------------------------------------
% This command is designed to customize the styling of the \chaper{} command to create a box with the chapter number along with a mini summary containing the page where each exercise and its solution are located.
\newcommand{\chapterNumberAndMinitoc}{%
\begin{tikzpicture}
    \node[
        minimum height = 1cm,
        inner sep = 2.5mm,
        text width = 0.97*\textwidth,
        align = left,
        fill = myDColor,
        anchor = north, % Changed from "east" to "north" to anchor by the top
    ] {
        \footnotesize
        \color{white}
        \begin{minipage}{\textwidth}
            \centering
            \textbf{Sections}
            \printcontents[sections]{}{1}{}{}
        \end{minipage}
    };
\end{tikzpicture}%
}
\titleformat{\chapter}[display]
{\normalfont\bfseries\color{myDColor}}
{\filleft% 
\chapterNumberAndMinitoc}{0.5em}
{\titlerule[2.5pt]\titlerule\vspace{4pt}\LARGE\textsc}
\titlespacing*{\chapter}{0pt}{-50pt}{20pt} % Adjusting spacing before and after the chapter title
% This command removes the blank page that is automatically created when you compile the text cover and then a chapter.
\makeatletter
\patchcmd{\chapter}{%
\if@openright
    \cleardoublepage
    \else
    \clearpage
\fi
}{%
}{}{}
\makeatother
% This command create a polygon on the left side of the section title
\newcommand{\polygonSection}{%
\begin{tikzpicture}[remember picture, overlay,baseline=1.5ex]
\node[%
    regular polygon sides   = 6, 
    rounded corners,
    regular polygon,
    minimum size            = 1.58cm,
    ultra thick,
    inner sep               = 0pt,
    fill                    = myLColor!85,
    anchor                  = south
] at (current page.north west |- 0,0) (red polygon) {};
\foreach \i in {2.5,...,4.5}{%
    \node[%
        myDColor,
        regular polygon sides   = 6, 
        regular polygon,
        rounded corners,
        minimum size            = \i cm,
        ultra thick,
        draw,
    ] at (red polygon) {};
}
\end{tikzpicture}}
\titleformat{\section}[display]
    {\vspace{2em}\normalfont\bfseries\color{myDColor}\huge}{}{}
    {\polygonSection\hspace{0.666em}}
% This command is a reformulation of the \section{} command, so that from now on, every time this command is called it will not compile the section number, only the title, but will still add this title in the table of contents
\let\oldsection\section                             
\renewcommand{\section}[1]{%                        
    \oldsection*{#1}                                
    \phantomsection                                
    \addcontentsline{toc}{section}{#1}              
}                                                    
\titlecontents{section}
[0em]
{}
{}
{}
{\titlerule*[0.4pc]{.}\contentspage}
% This command change the color of the label number in \label{} commands
\makeatletter
\def\tagform@#1{\maketag@@@{\normalfont(\color{myLColor}\ignorespaces#1\unskip\@@italiccorr\color{black})}}
\makeatother
%---------------------------------------------------------------------------
%	DOCUMENT COVER
%---------------------------------------------------------------------------
% Here the commands for building the document cover were made.
\newcommand{\pretitle}[4]{
\begin{titlepage}
\pagestyle{empty}
\begin{tikzpicture}[remember picture,overlay]
    % BACKGROUND
    \fill[myDColor] (current page.south west) rectangle (current page.north east);
    \foreach \i in {2.5,...,22}{%
        \node[%
            myDColor!60,
            regular polygon sides   = 6, 
            regular polygon,
            rounded corners,
            minimum size            = \i cm,
            ultra thick,
            draw,
        ] at ($(current page.west)+(2.5,-5)$) {};
    }
    % BACKGROUND POLYGONS
    \foreach \i in {0.5,...,22}{%
        \node[%
            myLColor!85,        
            regular polygon sides   = 6, 
            regular polygon,
            rounded corners,
            minimum size            = \i cm,
            ultra thick,
            draw,
        ] at ($(current page.north west)+(2.5,0)$) {};
    }
    \foreach \i in {0.5,...,22}{%
        \node[%
            myDColor!90,        
            regular polygon sides   = 6, 
            regular polygon,
            rounded corners,
            minimum size            = \i cm,
            ultra thick,
            draw,
        ] at ($(current page.north east)+(0,-10)$) {};
    }
    \foreach \i in {21,...,6}{%
        \node[
            myLColor!85,        
            regular polygon sides   = 6, 
            regular polygon,
            rounded corners,
            minimum size            = \i cm,
            ultra thick,
            draw,
        ] at ($(current page.south east)+(-0.2,0.1)$) {};
    }
    % TITLE
    \node[%
        myLColor!5,
        rounded corners,        
        minimum height  = 3cm,         
        minimum width   = 0.625*\paperwidth,
        left,
    ] (title) at ($(current page.north east)+(0,-10)$){%
        {\fontsize{25}{30} \selectfont \bfseries #1} % TITLE = #1
    };
    % SUBTITLE
    \node[%
        myLColor!10,
        rounded corners,
        minimum height  = 2cm, 
        minimum width   = 0.625*\paperwidth,        
        left,
    ] at ($(current page.north east)+(0,-11)$){%
        {\huge \textit{#2}} % SUBTITLE = #2
    };
    \node[%
        myLColor!10,
        rounded corners,
        minimum height  = 2cm, 
        minimum width   = 0.625*\paperwidth,        
        left,
    ] at ($(current page.north east)+(0,-12)$){%
        {\huge \textit{#3}} % SUBTITLE = #3
    };
    % AUTHOR NAME
    \node[%
        myLColor!5,
        rounded corners,
        minimum height  = 2cm, 
        minimum width   = 0.625*\paperwidth,
        left,
    ] at ($(current page.north east)+(0,-13)$){%
        {\Large \textsc{#4}} % NAME = #3
    };
    % YEAR
    \node[%
        regular polygon sides   = 6, 
        rounded corners,
        regular polygon,
        minimum size            = 2.5 cm,
        ultra thick,
        inner sep               = 0,
        fill                    = myLColor!85,
        text                    = myLColor!5,
    ] at ($(current page.west)+(2.5,-5)$) {\LARGE \bfseries \the\year};
    % Institute name
    \node[text = myLColor!5] (Institute) at ($(title.north)+(0,-0.5)$$) {College of Engineering \& Applied Sciences};
    % University logo
    \node[] at ($(Institute.north)+(0,1.5)$){\includegraphics[width=2.5cm]{Figures/CU Wordmark.png}};
    
\end{tikzpicture}
\end{titlepage}
}
%---------------------------------------------------------------------------
%	NEW ENVIRONMENTS AND NEW COMMANDS
%---------------------------------------------------------------------------
% This environment was made to produce a box which maintain the width and height of the text inside it.
\newtcolorbox{highlight}[1][]{%
    enhanced,
    skin first=enhanced,
    skin middle=enhanced,
    skin last=enhanced,
    before upper={\parindent15pt},
    breakable,
    boxrule = 0pt,
    frame hidden,
    borderline west = {4pt}{0pt}{myDColor},
    colback = myLColor!10,
    coltitle = myLColor!5,
    sharp corners,
    rounded corners = southeast,
    arc is angular,
    arc = 3mm,
    attach boxed title to top left,
    boxed title style = {%
        enhanced,
        colback = myDColor,
        colframe = myDColor,
        top = 0pt,
        bottom = 0pt,
        sharp corners,
        rounded corners = northeast,
        arc is angular,
        arc = 2mm,
        rightrule = 0pt,
        bottomrule = 0pt,
        toprule = 0pt,
    },
    title = {\bfseries\large #1}, 
    overlay unbroken={%
        \path[fill = tcbcolback!80!black] 
            ([yshift = 3mm]interior.south east) -- ++(-0.4,-0.1) -- ++(0.1,-0.2);
    },
    overlay first = {%
        \path[fill = tcbcolback!80!black] 
            ([yshift = 3mm]interior.south east) -- ++(-0.4,-0.1) -- ++(0.1,-0.2);
    },
    overlay middle={%
        \path[fill = tcbcolback!80!black] 
            ([yshift = -3mm]interior.north east) -- ++(-0.4,0.1) -- ++(0.1,0.2);
        \path[fill = tcbcolback!80!black] 
            ([yshift = 3mm]interior.south east) -- ++(-0.4,-0.1) -- ++(0.1,-0.2);
    },
    overlay last={%
        \path[fill = tcbcolback!80!black] 
            ([yshift = -3mm]interior.north east) -- ++(-0.4,0.1) -- ++(0.1,0.2);
        \path[fill = tcbcolback!80!black] 
            ([yshift = 3mm]interior.south east) -- ++(-0.4,-0.1) -- ++(0.1,-0.2);
    },
    extras middle and last = { rounded corners = northeast }
}
% The below commands was made to personalize the align and align* environments to have a orange line between to equalities.
\newcommand*\eqlineset{\pgfqkeys{/eqlines}}
\eqlineset{
    picture/.style={baseline, remember picture},
    line/.style={thick, draw=myLColor, line cap=round},
    node/.style={
    minimum size=+0pt, inner sep=+0pt, outer ysep=+.3333em, anchor=base,
    name=tma\thetikzmarkalign},
}
\newcounter{tikzmarkalign}
\makeatletter
\AtBeginEnvironment{align}{%
    \setcounter{tikzmarkalign}{0}%
    \newcommand*\noeq{\hphantom{={}}}%
    \newcommand*\eq{
    \ifnum\value{tikzmarkalign}=0
        \mathrel{\tikz[/eqlines/picture]\node[/eqlines/node]{$=$};}
    \else
        \mathrel{
        \begin{tikzpicture}[/eqlines/picture]
            \node[/eqlines/node] (tma\thetikzmarkalign) {$=$};
            \unless\ifmeasuring@
            \path[/eqlines/line, overlay] (tma\thetikzmarkalign)
                        -- (tma\pgfinteval{\thetikzmarkalign-1});
            \fi
        \end{tikzpicture}
        }
    \fi
    \stepcounter{tikzmarkalign}
    }%
}
\makeatother
\makeatletter
\AtBeginEnvironment{align*}{%
    \setcounter{tikzmarkalign}{0}%
    \newcommand*\noeq{\hphantom{={}}}%
    \newcommand*\eq{
    \ifnum\value{tikzmarkalign}=0
        \mathrel{\tikz[/eqlines/picture]\node[/eqlines/node]{$=$};}
    \else
        \mathrel{
        \begin{tikzpicture}[/eqlines/picture]
            \node[/eqlines/node] (tma\thetikzmarkalign) {$=$};
            \unless\ifmeasuring@
            \path[/eqlines/line, overlay] (tma\thetikzmarkalign)
                        -- (tma\pgfinteval{\thetikzmarkalign-1});
            \fi
        \end{tikzpicture}
        }
    \fi
    \stepcounter{tikzmarkalign}
    }%
}
\makeatother
\newcommand{\divider}{\setlength{\parindent}{0pt}\textcolor{myDColor!30}{\rule{\linewidth}{0.6pt}}\smallskip\setlength{\parindent}{1.0em}}
% This command was made to create a box (which can be labeled) to write equations which are answers for a random problem
\NewEnviron{highlightbox}{
\tcbhighmath[
        boxrule = 1pt,
        colframe = myLColor,
        colback = black!80,
        rounded corners,
        arc = 3mm,
        coltext = white,
    ]{\BODY}}
% This renewcommand was created to change the arrow notation from vectors to the bold notation of them.
\renewcommand\vec{\boldsymbol}
% This command was created to make comments inside the text using the a more beautifull " ".
\newcommand{\Acomment}[1]{\textquotedblleft \textit{#1}\textquotedblright }
% The below commands is to maintain the font to the symbol mathbb{1} different and more beauty
\DeclareMathAlphabet{\mathbbold}{U}{bbold}{m}{n}
\newcommand*{\boldone}{\mathbbold{1}}
%---------------------------------------------------------------------------
%	CUSTOM COMMANDS
%---------------------------------------------------------------------------
\newcommand{\modulo}{\text{ \textbf{mod} }}
\newcommand{\rem}[1]{\text{ \textbf{remainder }} \underbar{#1}}
\newcommand{\qed}{$\square$}
\newcommand{\horizontalline}[2]{
    \par % Ensure that we are in vertical mode
    \vskip#1em % Space above the line
    \noindent\rule{\textwidth}{0.5pt} % The line itself
    \par % Go back to vertical mode
    \vskip#2em % Space below the line
    \noindent % Ensures next paragraph does not indent
}
\lstnewenvironment{code}[1][]
{
    \lstset{style=stackoverflow, language=#1}
}
{}
\newenvironment{statement}[1]{
    \subsection*{#1}
    \begin{mdframed}[
        linewidth=1pt,
        linecolor=black,
        topline=true,
        bottomline=true,
        rightline=true,
        leftline=true,
        leftmargin=0pt,
        innerleftmargin=15pt,
        innerrightmargin=15pt]
    }
{\end{mdframed}}
\newenvironment{problem}[1]{
    \clearpage
    \section{#1}
    \horizontalline{0}{-1}
    }
{}
\newenvironment{summary}[1]
{
    \clearpage
    \subsection*{#1}
    \horizontalline{0}{-1}
    }
{}