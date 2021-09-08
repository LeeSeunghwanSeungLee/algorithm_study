'''
    === 전략 ===
1. genre, idx, plays 형태의 배열로 3차원으로 정렬 
2. 선형탐색을 하면서 2개씩 answer 에 주워담는다
3. return

이상 O(N*Log(N)) 성능을 보여줄 것으로 예상됨
'''

from collections import defaultdict
from operator import itemgetter

def solution(genres, plays):
    genre_play_dict = defaultdict(lambda: 0)
    
    for genre, play in zip(genres, plays):
        genre_play_dict[genre] += play
        
    genre_rank = [genre for genre, play in sorted(genre_play_dict.items(), key =itemgetter(1), reverse = True )]
    
    final_dict = defaultdict(lambda : [])
    for i, genre_play_tuple in enumerate(zip(genres, plays)):
        final_dict[genre_play_tuple[0]].append((genre_play_tuple[1], i))
        
    answer = []
    for genre in genre_rank:
        one_genre_list = sorted(final_dict[genre], key=itemgetter(0), reverse=True)
        if len(one_genre_list) > 1:
            answer.append(one_genre_list[0][1])
            answer.append(one_genre_list[1][1])
        else:
            answer.append(one_genre_list[0][1])
    return answer


    
from collections import defaultdict

# iterator
def counter():
    i = 0
    while True:
        yield i
        i += 1
        
def solution(genres, plays):
    play_count_by_genre = defaultdict(lambda: 0)
    songs_in_genre = defaultdict(list)
    
    for song_id, genre, play in zip(counter(), genres, plays):
        play_count_by_genre[genre] += play
        songs_in_genre[genre].append((-play, song_id))
        
    genre_in_order = sorted(play_count_by_genre.keys(), key = lambda g: play_count_by_genre[g], reverse= True)
    
    answer = []
    for genre in genre_in_order:
        answer.extend([ song_id for _, song_id in sorted(songs_in_genre[genre])[:2]])
    
    print(answer)