using System;
using System.Collections.Generic;


/**
 * @brief 커맨드라인 인자를 파싱하고 관리하는 클래스입니다.
 * 
 * @note 이 클래스는 정적 클래스로, 인스턴스 생성 없이 바로 사용할 수 있습니다.
 */
class CommandLine
{
    /**
     * @brief 명령행 인자를 파싱합니다.
     * 
     * @param Args 파싱할 명령행 인자입니다.
     */
    public static void Parse(string[] Args)
    {
        foreach (string Arg in Args)
        {
            string[] Tokens = Arg.Split('=');

            if (Tokens.Length == 2)
            {
                Arguments_.Add(Tokens[0], Tokens[1]);
            }
        }
    }


    /**
     * @brief 키 값에 대응하는 값이 존재하는지 확인합니다.
     * 
     * @param Key 값이 존재하는지 확인할 키 값입니다.
     * 
     * @return 키 값에 대응하는 값이 존재하면 true, 그렇지 않으면 false를 반환합니다.
     */
    public static bool IsValid(string Key)
    {
        return Arguments_.ContainsKey(Key);
    }


    /**
     * @brief 키 값에 대응하는 값을 얻습니다.
     * 
     * @param Key 얻을 값의 키 값입니다.
     * 
     * @return 키 값에 대응하는 값을 반환합니다.
     * 
     * @throws 키 값이 존재하지 않으면 예외를 던집니다.
     */
    public static string GetValue(string Key)
    {
        if(!IsValid(Key))
        {
            throw new Exception("invalid key in command line...");
        }

        return Arguments_[Key];
    }


    /**
     * @brief 명령행 인자의 키-값 쌍입니다.
     */
    private static Dictionary<string, string> Arguments_ = new Dictionary<string, string>();
}