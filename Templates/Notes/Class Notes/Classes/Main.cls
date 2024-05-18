%---------------------------------------------------------------------------
%	DOCUMENT VARIABLES
%---------------------------------------------------------------------------
\input{Classes/Core.cls}
\newcommand{\authorName}{Student Name}
\newcommand{\classCode}{Course Code}
\newcommand{\className}{Course Name}
\newcommand{\documentName}{Class Notes}
\newcommand{\universityName}{University Of Colorado}
%---------------------------------------------------------------------------
%	LOCAL DIRECTORIES
%---------------------------------------------------------------------------
\newcommand{\AssDir}{./Assignments/}
\newcommand{\LecNoteDir}{./Lecture Notes/}
\newcommand{\QuizDir}{./Quizzes/}
%---------------------------------------------------------------------------
%	CUSTOM COMMANDS
%---------------------------------------------------------------------------
\newcommand{\assignment}[2]{\due{(#1)} \cbox{#2}}
\newcommand{\cbox}[1]{\CheckBox[name=#1, width=0.75\baselineskip, height=0.75\baselineskip]{}}
\newcommand{\due}[1]{\textcolor{red}{#1}}
\newcommand{\horizontalline}[2]{
    \par
    \vskip#1em
    \noindent\rule{\textwidth}{0.5pt}
    \par
    \vskip#2em
    \noindent
}
\newcommand{\lecture}[3]{\link{#1}{#2}{ $\approx$ #3 \textbf{min}.}}
\newcommand{\link}[2]{\href{#1}{#2}}
\newcommand{\modulo}{\text{ \textbf{mod} }}
\newcommand{\pdflink}[2]{\href{run:#1}{#2}}
\newcommand{\qed}{$\square$}
\newcommand{\rem}[1]{\text{ \textbf{remainder }} \underbar{#1}}
\newcommand{\testimonial}[1]{
    \horizontalline{0}{0}
    \begin{center}
        \Large{\textbf{I have neither given nor received unauthorized assistance.}}
        \horizontalline{0}{0.5}
        \large{\textbf{\authorName}}
        \horizontalline{0}{0}
    \end{center}
    \noindent The original assignment for this problem can be found \pdflink{\AssDir #1}{here}.
}
%---------------------------------------------------------------------------
%	CUSTOM ENVIRONMENTS
%---------------------------------------------------------------------------
% Cheat sheet
\newenvironment{cheatsheet}[1]{
    \clearpage
    \twocolumn
    \subsection*{#1}
}
{\onecolumn \clearpage}
% Code
\lstnewenvironment{code}[1][]
{
    \lstset{style=stackoverflow, language=#1}
}
{}
% Exam notes
\newenvironment{examnotes}[1]{
    \clearpage
    \subsection*{#1}
}
{\clearpage}
% Notes
\newenvironment{notes}[1]
{
    \subsection*{#1}
    \horizontalline{0}{1}
}
{
    \horizontalline{1}{0}
}
% Problem
\newenvironment{problem}[1]{
    \clearpage
    \section{#1}
    \horizontalline{0}{-1}
}
{}
% Statement
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
% Summary
\newenvironment{summary}[1]
{
    \clearpage
    \subsection*{#1}
    \horizontalline{0}{-1}
    }
{}