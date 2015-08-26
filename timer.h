/**
 *  timer library contains three components, they are "timer, progress_timer" and "progress_display".
 *  Below will be detailed.
 */


/***************************************************************************/
/* header and namespace
/***************************************************************************/
#include <boost/timer.hpp>  
#include <boost/progress.hpp>  
#include <iostream>  
#include <sstream>  
#include <fstream>  
#include <vector>  

using namespace std;   
using namespace boost; 

 
/***************************************************************************/
/* timer
/***************************************************************************/
void timer_test() {
    // timer ����ʾ����timer �Դ�����Сʱ֮�ڣ��Ծ�ȷ�Ȳ��ߵ�ʱ��ͳ�ơ�  
    timer t;  
    cout << "�����ʱ�䣺" << t.elapsed_max() / 3600 << " h" << endl;  
    cout << "��С����ʱ�䣺" << t.elapsed_min() << " s" << endl;  
    cout << "�Ѿ���ȥʱ�䣺" << t.elapsed() << " s" << endl;  
    system("pause");  
    cout << "��ͣ��ȥʱ��:" << t.elapsed() << " s" << endl;  
    t.restart();  
    cout << "������ȥʱ��:" << t.elapsed() << " s" << endl;  
    system("pause");  
    cout << "��ͣ��ȥʱ��:" << t.elapsed() << " s" << endl;  
}
 
 
/***************************************************************************/
/*  progress_timer
/***************************************************************************/
void progress_timer_test() {
    // ʾ��1
    // progress_timer �̳��� timer ��ȫ������ 
    progress_timer t;    
    // �ֶ���ӡ�����ŵ�ʱ��
    cout << "progress_timer: " << t.elapsed() << endl;   

    // ʾ��2 
    // progress_timer ���������������Զ����ʱ��
    {  
        progress_timer t;  
    } 
      
    // ʾ��3
    // progress_timer ����ض����� stringstream ��   
    stringstream ss;  
    {  
        // ʹ progress_timer ����� ss
        progress_timer t(ss);  
    }  
    cout << "ss: " << ss.str() << endl;
}

/***************************************************************************/
/*  ��չ��ʱ����
/*  progress_timer �ľ���ֻ��С�������λ
/*  ������и��߾��ȵļ�ʱ�������Է��� progress_timer �Լ�дһ��
/***************************************************************************/
template <int N = 2>
class new_progress_timer : public boost::timer {
public:
    new_progress_timer(std::ostream & os = std::cout) : m_os(os) {
        // ����Ӧ��ʹ�þ�̬���Ե�
        assert(N >= 0 && N <= 10);
    }

    ~new_progress_timer() {
        try {
            // ��������״̬
            std::istream::fmtflags old_flags = m_os.setf(std::istream::fixed,
                std::istream::floatfield);
            std::streamsize old_prec = m_os.precision(N);

            // ���ʱ��
            m_os << elapsed() << " s" << std::endl;

            // �ָ�����״̬
            m_os.flags(old_flags);
            m_os.precision(old_prec);
        } catch (...) {}    // ���������������׳��쳣
    }
private:
    std::ostream m_os;
};

/** 
 *  ʹ��ģ���ػ�
 */
template<>
class new_progress_timer<2> : public boost::progress_timer {}; 


/***************************************************************************/
/*  progress_display
/*  ��ʾִ�н���
/***************************************************************************/
void progress_display_test() {
    // ���ڿ���̨��ʾ�����ִ�н��ȣ������޷��ѽ�����ʾ���������������� 
    vector<string> v(100);  
    ofstream fs("c:/test.txt");  
    // ��ʼ�����ȵĻ�����Ҳ�����ܽ���
    progress_display pd(v.size());  
      
    for (auto pos = v.begin(); pos != v.end(); ++pos) {  
        fs << *pos << endl;  
        // ���½�����ʾ
        ++pd;  
    }  
}
// ���ʾ��
// 0%   10   20   30   40   50   60   70   80   90   100% 
// |----|----|----|----|----|----|----|----|----|----| 
// ***************************************************