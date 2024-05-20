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
%	LOCAL PACKAGES
%---------------------------------------------------------------------------
\RequirePackage{ifthen} % Provides logical if then statements
%---------------------------------------------------------------------------
%	LOCAL DIRECTORIES
%---------------------------------------------------------------------------
% CSPB 2270
\newcommand{\CSPBDataStructDir}{./Courses/CSPB 2270 - Data Structures/}
\newcommand{\CSPBDataStructSyllabusDir}{\CSPBDataStructDir/Syllabus/}
\newcommand{\CSPBDataStructTextbookDir}{\CSPBDataStructDir/Textbook/}
\newcommand{\CSPBDataStructCourseNotes}{
    \pdflink{\CSPBDataStructDir CSPB 2270 - Data Structures Course Notes.pdf}{CSPB 2270 - Data Structures Course Notes}
}
\newcommand{\CSPBDataStructSyllabus}{
    \pdflink{\CSPBDataStructSyllabusDir CSPB 2270 - Data Structures Syllabus.pdf}{CSPB 2270 - Data Structures Syllabus}
}
\newcommand{\CSPBDataStructTextbook}{
    \pdflink{\CSPBDataStructTextbookDir CSPB 2270 - Data Structures Zybooks.pdf}{CSPB 2270 - Data Structures Zybooks}
}
% CSPB 2400
\newcommand{\CSPBCompSysDir}{./Courses/CSPB 2400 - Computer Systems/}
\newcommand{\CSPBCompSysSyllabusDir}{\CSPBCompSysDir/Syllabus/}
\newcommand{\CSPBCompSysTextbookDir}{\CSPBCompSysDir/Textbook/}
\newcommand{\CSPBCompSysCourseNotes}{
    \pdflink{\CSPBCompSysDir CSPB 2400 - Computer Systems Course Notes.pdf}{CSPB 2400 - Computer Systems Course Notes}
}
\newcommand{\CSPBCompSysSyllabus}{
    \pdflink{\CSPBCompSysSyllabusDir CSPB 2400 - Computer Systems Syllabus.pdf}{CSPB 2400 - Computer Systems Syllabus}
}
\newcommand{\CSPBCompSysTextbook}{
    \pdflink{\CSPBCompSysTextbookDir Computer Systems A Programmer's Perspective (Third Edition) - Randal E. Bryant, David R. O'Hallaron.pdf}{Computer Systems A Programmer's Perspective (Third Edition)}
}
% CSPB 2820
\newcommand{\CSPBLADir}{./Courses/CSPB 2820 - Linear Algebra With Computer Science Applications/}
\newcommand{\CSPBLASyllabusDir}{\CSPBLADir/Syllabus/}
\newcommand{\CSPBLATextbookDir}{\CSPBLADir/Textbook/}
\newcommand{\CSPBLACourseNotes}{
    \pdflink{\CSPBLADir CSPB 2820 - Linear Algebra With Computer Science Applications Course Notes.pdf}{CSPB 2820 - Linear Algebra With Computer Science Applications Course Notes}
}
\newcommand{\CSPBLASyllabus}{
    \pdflink{\CSPBLASyllabusDir CSPB 2280 - Linear Algebra With Computer Science Applications Syllabus.pdf}{CSPB 2280 - Linear Algebra With Computer Science Applications Syllabus}
}
\newcommand{\CSPBLAVMLSTextbook}{
    \pdflink{\CSPBLATextbookDir Introduction To Applied Linear Algebra (1st Edition) - Stephen Boyd And Lieven Vandenberghe.pdf}{Introduction To Applied Linear Algebra (1st Edition)}
}
\newcommand{\CSPBLAVMLSSolutions}{
    \pdflink{\CSPBLATextbookDir Introduction To Applied Linear Algebra Solutions Manual (1st Edition) - Stephen Boyd And Lieven Vandenberghe.pdf}{Introduction To Applied Linear Algebra Solutions Manual (1st Edition)}
}
\newcommand{\CSPBLAVMLSPyComp}{
    \pdflink{\CSPBLATextbookDir Introduction to Applied Linear Algebra, Vectors, Matrices, And Least Squares (1st Edition) - Jessica Leung And Dmytro Matsypura.pdf}{Introduction to Applied Linear Algebra, Vectors, Matrices, And Least Squares (1st Edition)}
}
% CSPB 2824
\newcommand{\CSPBDiscreteDir}{./Courses/CSPB 2824 - Discrete Structures/}
\newcommand{\CSPBDiscreteSyllabusDir}{\CSPBDiscreteDir/Syllabus/}
\newcommand{\CSPBDiscreteDirTextbookDir}{\CSPBDiscreteDir/Textbook/}
\newcommand{\CSPBDiscreteCourseNotes}{
    \pdflink{\CSPBDiscreteDir CSPB 2824 - Discrete Structures Course Notes.pdf}{CSPB 2824 - Discrete Structures Course Notes}
}
\newcommand{\CSPBDiscreteSyllabus}{
    \pdflink{\CSPBDiscreteSyllabusDir CSPB 2824 - Discrete Structures Syllabus.pdf}{CSPB 2824 - Discrete Structures Syllabus}
}
\newcommand{\CSPBDiscreteTextbook}{
    \pdflink{\CSPBDiscreteDirTextbookDir Discrete Mathematics And Its Applications (7th Edition) - Kenneth Rosen.pdf}{Discrete Mathematics And Its Applications (7th Edition)}
}
% CSPB 3022
\newcommand{\CSPBDataSciDir}{./Courses/CSPB 3022 - Introduction To Data Science With Probability And Statistics/}
\newcommand{\CSPBDataSciSyllabusDir}{\CSPBDataSciDir/Syllabus/}
\newcommand{\CSPBDataSciTextbookDir}{\CSPBDataSciDir/Textbook/}
\newcommand{\CSPBDataSciCourseNotes}{
    \pdflink{\CSPBDataSciDir CSPB 3022 - Introduction To Data Science With Probability And Statistics Course Notes.pdf}{CSPB 3022 - Introduction To Data Science With Probability And Statistics Course Notes}
}
\newcommand{\CSPBDataSciSyllabus}{
    \pdflink{\CSPBDataSciSyllabusDir CSPB 3022 - Introduction To Data Science With Probability And Statistics Syllabus.pdf}{CSPB 3022 - Introduction To Data Science With Probability And Statistics Syllabus}
}
\newcommand{\CSPBDataSciLearnDSTextbook}{
    \pdflink{\CSPBDataSciTextbookDir Learning Data Science Data Wrangling, Exploration, Visualization, and Modeling with Python (First Edition) - Sam Lau, Joseph Gonzalez, Deborah Nolanpdf.pdf}{Learning Data Science Data Wrangling, Exploration, Visualization, and Modeling with Python (First Edition)}
}
\newcommand{\CSPBDataSciPyForDSTextbook}{
    \pdflink{\CSPBDataSciTextbookDir Python for Data Analysis Data Wrangling with pandas, NumPy, and Jupyter (Third Edition) - Wes McKinney.pdf}{Python for Data Analysis Data Wrangling with pandas, NumPy, and Jupyter (Third Edition)}
}
% CSPB 3104
\newcommand{\CSPBAlgoDir}{./Courses/CSPB 3104 - Algorithms/}
\newcommand{\CSPBAlgoSyllabusDir}{\CSPBAlgoDir/Syllabus/}
\newcommand{\CSPBAlgoTextbookDir}{\CSPBAlgoDir/Textbook/}
\newcommand{\CSPBAlgoCourseNotes}{
    \pdflink{\CSPBAlgoDir CSPB 3104 - Algorithms Course Notes.pdf}{CSPB 3104 - Algorithms Course Notes}
}
\newcommand{\CSPBAlgoSyllabus}{
    \pdflink{\CSPBAlgoSyllabusDir CSPB 3104 - Algorithms Syllabus.pdf}{CSPB 3104 - Algorithms Syllabus}
}
\newcommand{\CSPBAlgoGrokkingTextbook}{
    \pdflink{\CSPBAlgoTextbookDir Grokking Algorithms An Illustrated Guide for Programmers and Other Curious People (First Edition) - Aditya Bhargava.pdf}{Grokking Algorithms An Illustrated Guide for Programmers and Other Curious People (First Edition)}
}
\newcommand{\CSPBAlgoIntroTextbook}{
    \pdflink{\CSPBAlgoTextbookDir Introduction to Algorithms (Third Edition) - Cormen, Thomas H. Leiserson, Charles E. Rivest, Ronald L. Stein.pdf}{Introduction to Algorithms (Third Edition)}
}
% CSPB 3155
\newcommand{\CSPBPPLDir}{./Courses/CSPB 3155 - Principles Of Programming Languages/}
\newcommand{\CSPBPPLSyllabusDir}{\CSPBPPLDir/Syllabus/}
\newcommand{\CSPBPPLTextbookDir}{\CSPBPPLDir/Textbook/}
\newcommand{\CSPBPPLSyllabus}{
    \pdflink{\CSPBPPLSyllabusDir CSPB 3155 - Principles of Programming Languages Syllabus.pdf}{CSPB 3155 - Principles of Programming Languages Syllabus}
}
\newcommand{\CSPBAtomicScalaTextbook}{
    \pdflink{\CSPBPPLTextbookDir Atomic Scala - Learn Programming In The Language Of The Future (Second Edition) - Dianne Marsh, Bruce Eckel.pdf}{Atomic Scala - Learn Programming In The Language Of The Future (Second Edition)}
}
\newcommand{\CSPBEssenPPLTextbook}{
    \pdflink{\CSPBPPLTextbookDir Essentials Of Programming Languages (Third Edition) - Daniel P. Friedman, Mitchell Wand.pdf}{Essentials Of Programming Languages (Third Edition)}
}
\newcommand{\CSPBFuncProgTextbook}{
    \pdflink{\CSPBPPLTextbookDir Functional Programming In Scala (First Edition) - Paul Chiusano, Runar Bjarnason.pdf}{Functional Programming In Scala (First Edition)}
}
\newcommand{\CSPBProgInScalTextbook}{
    \pdflink{\CSPBPPLTextbookDir Programming In Scala (Third Edition) - Martin Odersky, Lex Spoon, Bill Venners.pdf}{Programming In Scala (Third Edition)}
}
% CSPB 3202
\newcommand{\CSPBAIDir}{./Courses/CSPB 3202 - Introduction To Artifical Intelligence/}
\newcommand{\CSPBAISyllabusDir}{\CSPBAIDir/Syllabus/}
\newcommand{\CSPBAITextbookDir}{\CSPBAIDir/Textbook/}
\newcommand{\CSPBAISyllabus}{
    \pdflink{\CSPBAISyllabusDir CSPB 3202 - Artificial Intelligence Syllabus.pdf}{CSPB 3202 - Artificial Intelligence Syllabus}
}
\newcommand{\CSPBAITextbook}{
    \pdflink{\CSPBAITextbookDir Artificial Intelligence - A Modern Approach (Fourth Edition) - Stuart Russel, Peter Norvig.pdf}{Artificial Intelligence - A Modern Approach (Fourth Edition)}
}
\newcommand{\CSPBRLTextbook}{
    \pdflink{\CSPBAITextbookDir Reinforcement Learning - An Introduction (Second Edition) - Richard Sutton, Andrew Barto.pdf}{Reinforcement Learning - An Introduction (Second Edition)}
}
% CSPB 3308
\newcommand{\CSPBSoftDevDir}{./Courses/CSPB 3308 - Software Development Methods And Tools/}
\newcommand{\CSPBSoftDevSyllabusDir}{\CSPBSoftDevDir/Syllabus/}
\newcommand{\CSPBSoftDevTextbookDir}{\CSPBSoftDevDir/Textbook/}
\newcommand{\CSPBSoftDevSyllabus}{
    \pdflink{\CSPBSoftDevSyllabusDir CSPB 3308 - Software Development Methods And Tools Syllabus.pdf}{CSPB 3308 - Software Development Methods And Tools Syllabus}
}
\newcommand{\CSPBSoftDevAgileTextbook}{
    \pdflink{\CSPBSoftDevTextbookDir Agile For Dummies (Limited Edition) - Scott Ambler, Matthew Holitza.pdf}{Agile For Dummies (Limited Edition)}
}
\newcommand{\CSPBSoftDevEngTextbook}{
    \pdflink{\CSPBSoftDevTextbookDir Engineering Software As A Service - An Agile Approach Using Cloud Computing (First Edition) - Armando Fox, David Patterson.pdf}{Engineering Software As A Service - An Agile Approach Using Cloud Computing (First Edition)}
}
\newcommand{\CSPBSoftDevProGitTextbook}{
    \pdflink{\CSPBSoftDevTextbookDir Pro Git (Second Edition) - Scott Chacon, Ben Straub.pdf}{Pro Git (Second Edition)}
}
\newcommand{\CSPBSoftDevLinuxTextbook}{
    \pdflink{\CSPBSoftDevTextbookDir The Linux Command Line (Fifth Edition) - William Shotts.pdf}{The Linux Command Line (Fifth Edition)}
}
% CSPB 3702
\newcommand{\CSPBCogSciDir}{./Courses/CSPB 3702 - Cognitive Science/}
\newcommand{\CSPBCogSciSyllabusDir}{\CSPBCogSciDir/Syllabus/}
\newcommand{\CSPBCogSciReadMatDir}{\CSPBCogSciDir/Reading Material/}
\newcommand{\CSPBCogSciCourseNotes}{
    \pdflink{\CSPBCogSciDir CSPB 3702 - Cognitive Science Course Notes.pdf}{CSPB 3702 - Cognitive Science Course Notes}
}
\newcommand{\CSPBCogSciSyllabus}{
    \pdflink{\CSPBCogSciSyllabusDir CSPB 3702 - Cognitive Science Syllabus.pdf}{CSPB 3702 - Cognitive Science Syllabus}
}
\newcommand{\CSPBCMAndIntel}{
    \pdflink{\CSPBCogSciReadMatDir Computing Machinery And Intelligence.pdf}{Computing Machinery And Intelligence}
}
\newcommand{\CSPBEvol}{
    \pdflink{\CSPBCogSciReadMatDir Evolutionary Game Theory.pdf}{Evolutionary Game Theory}
}
\newcommand{\CSPBExpInPsych}{
    \pdflink{\CSPBCogSciReadMatDir Experiments In Synthetic Psychology.pdf}{Experiments In Synthetic Psychology}
}
\newcommand{\CSPBTitForTat}{
    \pdflink{\CSPBCogSciReadMatDir Is Tit-for-Tat The Answer?.pdf}{Is Tit-for-Tat The Answer?}
}
\newcommand{\CSPBHeuristics}{
    \pdflink{\CSPBCogSciReadMatDir Judgement Under Uncertainty - Heuristics And Biases.pdf}{Judgement Under Uncertainty - Heuristics And Biases}
}
\newcommand{\CSPBMentalImag}{
    \pdflink{\CSPBCogSciReadMatDir Mental Imagery And The Visual System.pdf}{Mental Imagery And The Visual System}
}
\newcommand{\CSPBMindBody}{
    \pdflink{\CSPBCogSciReadMatDir Mind, Body, World: Foundations of Cognitive Science.pdf}{Mind, Body, World: Foundations of Cognitive Science}
}
\newcommand{\CSPBMindsBrain}{
    \pdflink{\CSPBCogSciReadMatDir Minds, Brains, And Programs.pdf}{Minds, Brains, And Programs}
}
\newcommand{\CSPBPixel}{
    \pdflink{\CSPBCogSciReadMatDir Pixel Tutorial.pdf}{Pixel Tutorial}
}
\newcommand{\CSPBProsTheory}{
    \pdflink{\CSPBCogSciReadMatDir Prospect Theory.pdf}{Prospect Theory}
}
\newcommand{\CSPBRecogProb}{
    \pdflink{\CSPBCogSciReadMatDir Recognizing, Defining, and Representing Problems.pdf}{Recognizing, Defining, and Representing Problems}
}
\newcommand{\CSPBCollActions}{
    \pdflink{\CSPBCogSciReadMatDir The Evolution Of Institutions For Collective Action.pdf}{The Evolution Of Institutions For Collective Action}
}
\newcommand{\CSPBNatMental}{
    \pdflink{\CSPBCogSciReadMatDir The Nature of Mental States.pdf}{The Nature of Mental States}
}
\newcommand{\CSPBVision}{
    \pdflink{\CSPBCogSciReadMatDir Vision.pdf}{Vision}
}
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