import java.util.Queue;
import java.util.LinkedList;

class Solution {
    static int[][] map;
    static int answer;
    //character->item(목표 포인트)
    public int solution(int[][] rectangle, int characterX, int characterY, int itemX, int itemY) {
        answer=0;
        
        //1) map을 만든다.
        map= new int[101][101];
        
        //2) 좌표에 따라 map에 값을 넣을건데, 테두리에만 1을 넣을것이다.(*좌표는 두배로)
        for(int i=0; i<rectangle.length; i++){
            fill(2*rectangle[i][0], 2*rectangle[i][1], 2*rectangle[i][2], 2*rectangle[i][3]);
        }
        
        //3) bfs로 테두리 따라 양쪽으로 가보고 min값 채택
        bfs(2*characterX, 2*characterY, 2*itemX, 2*itemY);
        
        return answer/2;
    }
    
    //x1,y1,x2,y2 => (x1,y1)~(x2,y1), (x1,y2)~(x2,y2), (x1,y1)~(x1,y2), (x2,y1)~(x2,y2)
    //편하게 x2 해준 좌표를 받는다.
    public void fill(int x1, int y1, int x2, int y2) {
        for(int i=x1; i<=x2; i++){
            for(int j=y1; j<=y2; j++){
                if(map[i][j]==2) continue;
                map[i][j]=2;
                if(i==x1||i==x2||j==y1||j==y2){
                    map[i][j]=1;
                }
            }
        }
    }//fill
    
    static int[] dx= {-1, 0, 0, 1};
    static int[] dy= {0, -1, 1, 0};
    public void bfs(int startx, int starty, int itemx, int itemy){
        boolean[][] visited= new boolean[101][101];
        Queue<Integer> queue= new LinkedList<>();
        queue.add(startx);
        queue.add(starty);
        
        while(!queue.isEmpty()){
            int x= queue.poll();
            int y= queue.poll();
            
            for(int i=0; i<4; i++){
                int nx= x+dx[i];
                int ny= y+dy[i];
                if(!check(nx, ny)) continue; //범위 아웃
                if(map[nx][ny]!=1||visited[nx][ny]) continue;
                
                //map[nx][ny]==2이고 방문한적없음
                map[nx][ny]=map[x][y]+1;
                if(nx==itemx&&ny==itemy){ //목표점 도달
                    answer= (answer==0)? map[nx][ny]:Math.min(answer,map[nx][ny]);
                    continue;
                }
                visited[nx][ny]= true;
                queue.add(nx);
                queue.add(ny);
            }
        }
    }//bfs
    
    public boolean check(int x, int y){
        if(x<0||y<0||x>100||y>100) return false;
        return true;
    }
}
