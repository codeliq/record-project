# record-project\n
A.	프로젝트 명: record site server
B.	프로젝트 멤버 이름 및 멤버 별로 담당한 파트에 대한 소개: 강민정 
C.	프로젝트 소개 및 개발 내용 소개 
- TCP 통신을 하는 인터넷 도메인 소켓 통신을 사용하여 음반 사이트 서버(record sever)를
구축하고 여러 고객이 클라이언트로서 서버에 접속할 수 있다. 
- 클라이언트는 음반 리스트 확인, 원하는 음반의 재고 확인, 원하는 수량만큼 구매, 고객센터 기능 탑재 
- 서버는 클라이언트의 요청을 확인하고 요청된 데이터를 클라이언트에게로 전송 
- 모든 데이터는 파일로 관리됨. (음반 리스트 및 재고) 
- 고객센터를 통해 서버와 클라이언트 1:1 대화 가능 
 
D.	프로젝트 개발 결과물 소개 (+ 다이어그램) 
![image](https://user-images.githubusercontent.com/45085524/145193086-9030c963-d34c-4d98-81b3-6e402dcfe446.png) 
- 고객 클라이언트는 서버로 음반 리스트 확인/특정 음반에 대한 재고 확인 요청을 보낼 수 있다. 
- 요청이 들어오면 서버는 조회 결과를 저장된 파일로부터 읽어와 클라이언트에게 전송해준다. 
- 고객은 원하는 수량만큼 음반을 구매할 수 있다. 
- 구매 요청이 들어오면 서버는 저장된 파일에서 고객이 원하는 음반의 재고 수량 위치를 찾고 구매 수량만큼 뺀 계산값으로 파일에 다시 수정하여 저장함. (재고 업데이트) 
- 고객이 고객센터 요청시, 관리자(서버)와 클라이언트는 서로 1:1 통신하며 대화를 주고 받을 수 있다. 
- 서버에 동시에 여러명의 클라이언트가 접속할 수 있다.
 
E.	개발 결과물을 사용하는 방법 소개 (+ 프로그램 구동 화면 스크린 샷 첨부) 
<클라이언트> 
![image](https://user-images.githubusercontent.com/45085524/145194350-87eb1558-efac-4c38-b87f-89edcb9b6863.png) 
처음 실행시 클라이언트는 메뉴를 전송받아 선택할 수 있다. 
1번(음반 목록 확인) 선택 시, 음반 목록을 전송받아 출력된 것을 확인. 
또한, 메뉴를 계속 선택할 수 있다. 

![image](https://user-images.githubusercontent.com/45085524/145194594-158f8722-ac24-4515-9ff8-caa8dacca1fa.png) 
다시 메뉴에서 2번(재고 확인) 선택 시, 위에서 확인한 앨범 리스트를 보고 원하는 음반의 재고 수량을 확인할 수 있음. 
리스트 확인에서 두번째(NCT) 앨범의 재고 수량을 확인함.  -> 224006장

![image](https://user-images.githubusercontent.com/45085524/145194911-bef9ea83-66f6-48f4-abaf-24b23c3f0eaf.png)
다시 메뉴에서 3번(구매) 선택 시, 원하는 앨범(2번째,NCT)의 원하는 수량만큼 구매 가능.(300장 구매)
![image](https://user-images.githubusercontent.com/45085524/145195307-50e5e523-4c21-4643-a603-a845380451c0.png)
다시 수량 확인시 300장이 줄어든 것을 확인.

![image](https://user-images.githubusercontent.com/45085524/145195469-dda0e497-67f5-468f-9791-c41a21b19f10.png)
메뉴에서 4번(고객센터) 선택 시, 서버와 1:1 대화가 가능하며 EXIT시 종료함.

<서버>
![image](https://user-images.githubusercontent.com/45085524/145195573-028a8285-a700-40f6-aa05-9b935da84d64.png)
클라이언트의 접속 여부 및 어떤 요청(메뉴 선택)을 했는지 확인할 수 있다.
또한, 고객센터 요청시 1:1 대화를 가능하다.


F.	개발 결과물의 필요성 및 활용방안
협소한 구현이지만, 실제 웹 서버로서 동작하도록 사용자 인터페이스 등 보완을 하게 된다면 실제처럼 동작하는 음반 사이트 혹은 일반 쇼핑몰을 구현해볼 수 있는 기대를 가진다.

