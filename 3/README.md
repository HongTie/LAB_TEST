# Task_3

Info:  
  This program demonstrates how a server and a client receive and return messages.


## Usage instructions are as follows:  
Method 1:  
1.啟動兩個.bat檔案，分別為launch_server與launch_client(功能如字面上,要先啟動server在啟動client)  
2.啟動成功後就能在client端輸入東西，server會回傳回來，client會顯示收到回傳 

Method 2:  
1.open cmd  
2.cd to file path where '\3' located in.  
3.enter this  
```.\server.exe 8080```   
to active the server.
4. repeat step 1.2. and replace 3.'s instruction with  
```.\client.exe 127.0.0.1 8080```   
to active the client.  


如果需要重新compile source code,請使用以下指令:  
```
gcc -o client client.c -lws2_32
gcc -o server server.c -lws2_32
```
*************************
Made by Wei-ting Hsu  
2025/3/19  
editor:VScode  

*************************
