program SLAU
    use m_Interface
    use m_MyMatrixLyb

    character(20) FileName
    Integer RazmerM, Metod
    real N
    integer,dimension(1:8):: TimeS, TimeE

    write(*,*)"Vvedite imya fajla, kotoryj sodepzhit vashu matricu:"
    write(*,*)"Pozhalujsta, pomnite o tom, chto on dolzhen sushchestvovat'"
    read(*,*) FileName
    write(*,*)"Vvedite razmer vashej matricy:"
    read(*,*) RazmerM
    write(*,*)" "
    write(*,*)"Proverka na obuslovlennost':"

    N = f_COND(f_ReadMatrix(FileName,RazmerM))
    if (N<=10.) then
        write(*,*)"Matrica horosho obsulovlena"
    else
        if (N<=100.) then
            write(*,*)"Matrica ploho obsulovlena"
            write(*,*)"(Dannye sleduet proverit' na korrektnost')"
        else
            write(*,*)"Reshenie zavedomo neverno"
        end if
    end if
    rewind(1)

    write(*,*)" "
    write(*,*)"Vyberete metod resheniya:"
    write(*,*)"1. Metod Gaussa"
    write(*,*)"2. Metod Progonki"
    write(*,*)"   (Dlya trekhdiagonal'noj matricy)"
    write(*,*)"3. Metod Seidelya"
    read(*,*) Metod

    select case(Metod)
        case(1)
            call date_and_time(values = TimeS)
            call s_Gauss(f_ReadMatrix(FileName,RazmerM), RazmerM)
            call date_and_time(values = TimeE)
        case(2)
            call date_and_time(values = TimeS)
            call s_Progonka(f_ReadMatrix(FileName,RazmerM), RazmerM)
            call date_and_time(values = TimeE)
        case(3)
            write(*,*)"Vvedite dopustimuyu pogreshnost'"
            read(*,*) N
            call date_and_time(values = TimeS)
            call s_Seidel(f_ReadMatrix(FileName,RazmerM), RazmerM, N)
            call date_and_time(values = TimeE)
        case default
            write(*,*)"Ya ne znayu takih metodov"
    end select

        TimeE(6) = TimeE(6)-TimeS(6)
        TimeE(7) = TimeE(7)-TimeS(7)
        TimeE(8) = TimeE(8)-TimeS(8)

        write(*,*)"Raschet zanyal:"
        write(*,*) TimeE(6), " minut, ", TimeE(7), " sekund, ", TimeE(8), " millisekund"

    read(*,*)
end program