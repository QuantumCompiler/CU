%---------------------------------------------------------------------------
%	DOCUMENT VARIABLES
%---------------------------------------------------------------------------
\input{Classes/GoldenCommands.cls}
\newcommand{\authorName}{Taylor Larrechea}
\newcommand{\classCode}{CSPB}
\newcommand{\className}{CSPB Encyclopedia}
\newcommand{\documentName}{Curriculum Encyclopedia}
\newcommand{\universityName}{University Of Colorado}
%---------------------------------------------------------------------------
%	COURSE COMMANDS
%---------------------------------------------------------------------------
\newcommand{\CSPBIntro}{CSPB 1300 - Computer Science 1: Starting Computing}
\newcommand{\CSPBDataStruct}{CSPB 2270 - Computer Science 2: Data Structures}
\newcommand{\CSPBCompSys}{CSPB 2400 - Computer Systems}
\newcommand{\CSPBDisc}{CSPB 2824 - Discrete Structures}
\newcommand{\CSPBAlgo}{CSPB 3104 - Algorithms}
\newcommand{\CSPBPPL}{CSPB 3155 - Principles Of Programming Languages}
\newcommand{\CSPBSoftDev}{CSPB 3308 - Software Development Methods And Tools}
\newcommand{\CSPBLA}{CSPB 2820 - Linear Algebra With Computer Science Applications}
\newcommand{\CSPBDataSci}{CSPB 3022 - Introduction to Data Science With Probability \& Statistics}
\newcommand{\CSPBAI}{CSPB 3202 - Introduction to Artificial Intelligence}
\newcommand{\CSPBDataBase}{CSPB 3287 - Design \& Analysis of Database Systems}
\newcommand{\CSPBCogSci}{CSPB 3702 - Cognitive Science}
\newcommand{\CSPBOS}{CSPB 3753 - Design \& Analysis of Operating Systems}
\newcommand{\CSPBIV}{CSPB 4122 - Information Visualization}
\newcommand{\CSPBDM}{CSPB 4502 - Data Mining}
\newcommand{\CSPBML}{CSPB 4622 - Machine Learning}
%---------------------------------------------------------------------------
%	LOCAL DIRECTORIES
%---------------------------------------------------------------------------
% CSPB 2270
\newcommand{\CSPBDataStructDir}{./Courses/CSPB 2270 - Data Structures/}
\newcommand{\CSPBDataStructSyllabusDir}{\CSPBDataStructDir/Syllabus/}
\newcommand{\CSPBDataStructTextbookDir}{\CSPBDataStructDir/Textbook/}
% CSPB 2400
\newcommand{\CSPBCompSysDir}{./Courses/CSPB 2400 - Computer Systems/}
\newcommand{\CSPBCompSysSyllabusDir}{\CSPBCompSysDir/Syllabus/}
\newcommand{\CSPBCompSysTextbookDir}{\CSPBCompSysDir/Textbook/}
% CSPB 2820
\newcommand{\CSPBLADir}{./Courses/CSPB 2820 - Linear Algebra With Computer Science Applications/}
\newcommand{\CSPBLASyllabusDir}{\CSPBLADir/Syllabus/}
\newcommand{\CSPBLATextbookDir}{\CSPBLADir/Textbook/}
% CSPB 2824
\newcommand{\CSPBDiscreteDir}{./Courses/CSPB 2824 - Discrete Structures/}
\newcommand{\CSPBDiscreteSyllabusDir}{\CSPBDiscreteDir/Syllabus/}
\newcommand{\CSPBDiscreteDirTextbookDir}{\CSPBDiscreteDir/Textbook/}
% CSPB 3022
\newcommand{\CSPBDataSciDir}{./Courses/CSPB 3022 - Introduction To Data Science With Probability And Statistics/}
\newcommand{\CSPBDataSciSyllabusDir}{\CSPBDataSciDir/Syllabus/}
\newcommand{\CSPBDataSciTextbookDir}{\CSPBDataSciDir/Textbook/}
% CSPB 3104
\newcommand{\CSPBAlgoDir}{./Courses/CSPB 3104 - Algorithms/}
\newcommand{\CSPBAlgoSyllabusDir}{\CSPBAlgoDir/Syllabus/}
\newcommand{\CSPBAlgoTextbookDir}{\CSPBAlgoDir/Textbook/}
% CSPB 3702
\newcommand{\CSPBCogSciDir}{./Courses/CSPB 3702 - Cognitive Science/}
\newcommand{\CSPBCogSciSyllabusDir}{\CSPBCogSciDir/Syllabus/}
\newcommand{\CSPBCogSciReadMatDir}{\CSPBCogSciDir/Reading Material/}
%---------------------------------------------------------------------------
%	CUSTOM COMMANDS
%---------------------------------------------------------------------------
% Course
\newcommand{\course}[2]{
    \horizontalline{0}{0}
    \noindent {\color{myLColor}{\textbf{#1}}} \\
    \horizontalline{-1.5}{0}
    #2
}
% Document hyperlink
\newcommand{\doclink}[2]{
    \begingroup
    \hypersetup{linkcolor=black}
    \hyperlink{#1}{\textbf{#2}}
    \endgroup
}
% Course document link
\newcommand{\coursedoc}[1]{
    \begin{center}
        \begin{highlightbox}
            \text{#1}
        \end{highlightbox}
    \end{center}
}
% Cell coloring
\renewcommand{\arraystretch}{1.25}
\newcommand{\cyancell}{\cellcolor{cyan!25}}
\newcommand{\graycell}{\cellcolor{gray!25}}
\newcommand{\greencell}{\cellcolor{green!25}}
\newcommand{\greycell}{\cellcolor{gray!65}}
\newcommand{\magentacell}{\cellcolor{magenta!25}}
\newcommand{\orangecell}{\cellcolor{orange!25}}
\newcommand{\redcell}{\cellcolor{red!50}}
\newcommand{\yellowcell}{\cellcolor{yellow!25}}
\newcommand{\coreclass}{\yellowcell}
\newcommand{\electiveclass}{\graycell}
\newcommand{\credithours}[1]{\cyancell #1}
\newcommand{\header}[1]{\greycell #1}
\newcommand{\completed}[1]{\greencell \footnotesize Completed - #1}
\newcommand{\inprogress}[1]{\orangecell \footnotesize In Progress - #1}
\newcommand{\scheduled}[1]{\magentacell \footnotesize Scheduled - #1}
\newcommand{\notsched}{\redcell \footnotesize Not Scheduled}