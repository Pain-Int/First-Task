module m_MyMatrixLyb
    implicit none

    contains

    real function f_NormaM(A)
        real,dimension(:,:), intent(In):: A
        integer I, J

        f_NormaM = 0.

        do I=1, size(A,1)
            do J=1, size(A,2)
                f_NormaM = f_NormaM + A(I,J)**2
            end do
        end do

        f_NormaM = sqrt(f_NormaM)
    end function

    real function f_det(A)
        real,dimension(:,:), intent(In):: A
        real,dimension(1:size(A,1),1:size(A,1)):: B
        real,dimension(1:size(A,1)):: Buffer
        integer I, J

        B = A
        !приводим к треугольному виду
        do I=1, size(A,1)
            if(B(I,I) == 0.) then
                Buffer = B(I,:)
                B(I,:) = B(I+1,:)
                B(I+1,:) = Buffer
                Buffer = 0
            end if

            do J=I+1, size(A,1)
                B(J,:) = B(J,:) - ( B(I,:)*B(J,I)/B(I,I) )
            end do
        end do

        f_det = A(1,1)
        do I=2, size(A,1)
            f_det = f_det*B(I,I)
        end do
    end function

    function f_Obrat(A)
        real,dimension(:,:), intent(In):: A
        real,dimension(1:size(A,1),1:size(A,1)):: f_Obrat
        real,dimension(1:size(A,1),1:size(A,1)):: Az
        integer I,J

        if(f_det(A)==0.) then
            Write(*,*)'Determinant is NULL'
            return
        else
            do I=1, size(A,1)
                do J=1, size(A,1)
                    Az(J,I) = f_AlgDop(A,I,J)
                end do
            end do

            f_Obrat = 1/f_det(A)*Az

            !do I=1, size(A,1)
            !    write(*,*) f_Obrat(I,:)
            !end do
        end if
    end function

    real function f_AlgDop(A,i,j)
        real,dimension(:,:), intent(In):: A
        real,dimension(1:size(A,1)-1,1:size(A,1)-1):: Minor
        integer, intent(In):: i,j

            Minor(:i-1,:j-1) = A(:i-1,:j-1)
            Minor(i:,:j-1) = A(i+1:,:j-1)
            Minor(:i-1,j:) = A(:i-1,j+1:)
            Minor(i:,j:) = A(i+1:,j+1:)

            f_AlgDop = (-1)**(i+j)*f_det(Minor)
    end function

    real function f_COND(A)
        real,dimension(:,:), intent(In):: A

        f_COND = f_NormaM(A)*f_NormaM(f_Obrat(A))
    end function    
end module