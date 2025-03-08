#include<iostream>
using namespace std;
#include<unordered_map>
#include<list>


class Movie{
    private:
        string movieName;
        int movieId;
        int movieDurationInMin;

    public:
        int getMovieId(){
            return movieId;
        }

        void setMovieId(int id){
            this->movieId = id;
        }

        string getMovieName(){
            return movieName;
        }

        void setMovieName(string name){
            this->movieName = name;
        }

        int setMovieDurationInMin(){
            return this->movieDurationInMin;
        }

        void getMovieDurationInMin(int duration){
            this->movieDurationInMin = duration;
        }
};

class City{

};


class MoviesController {
    private:
        unordered_map<City,list<Movie>> moviesListByCity;
        list<Movie> allMovies;

    public:

        MoviesController(unordered_map<City,list<Movie>> CityVsMovie, list<Movie> allMovies){
            this->moviesListByCity = CityVsMovie;
            this->allMovies = allMovies;
        }

        MoviesController(){
            
        }

        void addMovie(Movie movie, City city){
            moviesListByCity[city].emplace_back(movie);
            allMovies.emplace_back(movie);
        }


};


int main(){

    Movie m;
    m.setMovieId(5);

    cout<<m.getMovieId();


    return 0;
}
