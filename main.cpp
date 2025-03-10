#include<iostream>
#include<unordered_map>
#include<map>
#include<list>
#include <string>

using namespace std;

enum class City{
    Noida,
    Agra
};

enum class SeatCategory{
    Silver,
    Gold,
    Platinum
};

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

        int getMovieDurationInMin(){
            return this->movieDurationInMin;
        }

        void setMovieDurationInMin(int duration){
            this->movieDurationInMin = duration;
        }
};

class MoviesController {
    private:
        unordered_map<City,list<Movie>> moviesListByCity;
        list<Movie> allMovies;

    public:

        MoviesController(unordered_map<City,list<Movie>> &CityVsMovie, list<Movie> &allMovies){
            this->moviesListByCity = CityVsMovie;
            this->allMovies = allMovies;
        }

        MoviesController() : moviesListByCity(), allMovies(){}

        void addMovie(Movie movie, City city){
            moviesListByCity[city].push_back(movie);
            allMovies.push_back(movie);
        }

        list<Movie> getMovieByCity(City city){
            return moviesListByCity[city];
        }

        Movie* getMovieByName(string name){
            for(auto movie : allMovies){
                if(movie.getMovieName()==name){
                    return &movie;
                }
            }

            return nullptr;
        }
};

class Seat{
    private:
        int seatId;
        int row;
        SeatCategory seatCategory;

    public:
        void setSeatId(int id){
            this->seatId = id;
        }

        int getSeatId(){
            return seatId;
        }

        void setRow(int row){
            this->row = row;
        }

        int getRow(){
            return row;
        }

        void setSeatCategory(SeatCategory sc){
            this->seatCategory = sc;
        }

        SeatCategory getSeatcategory(){
            return this->seatCategory;
        }
};




class Screen{
    private:
        int screenId;
        list<Seat> seats;

    public:

        void setScreenId(int id){
            this->screenId = id;
        }

        int getScreenId(){
            return this->screenId;
        }

        void setSeats(list<Seat> &seats){
            this->seats = seats;
        }

        list<Seat> getSeats(){
            return this->seats;
        }
};

class Show{
    private:
        int showStartTime;
        int showId;
        list<int> bookedSeatsId;
        Movie movie;
        Screen screen;

    public:
        void setStartTime(int time){
            this->showStartTime = time;
        }

        int getStartTime(){
            return this->showStartTime;
        }

        void setShowId(int id){
            showId=id;
        }

        int getShowId(){
            return showId;
        }

        void setMovie(Movie movie){
            this->movie = movie;
        }

        Movie getMovie(){
            return movie;
        }

        void setScreen(Screen scrn){
            screen = scrn;
        }

        void bookSeat(int seat){
            bookedSeatsId.push_back(seat);
        }

        list<int> getListOfSeatsBooked(){
            return bookedSeatsId;
        } 
};

class Theatre{
    private:
        int threaterId;
        string address;
        City city;
        list<Show> show;
        list<Screen> screen;

    public:
        
        void setTheaterId(int id){
            this->threaterId = id;
        }

        int getTheaterId(){
            return this->threaterId;
        }

        void setTheaterAddress(string address){
            this->address = address;
        }

        void setCity(City city){
            this->city = city;
        }

        City getCity(){
            this->city;
        }

        void setShows(list<Show> &show){
            this->show = show;
        }

        list<Show> getShows(){
            return this->show;
        }

        void setScreens(list<Screen> screens){
            this->screen = screens;
        }
};

class TheaterController{
    private:
        unordered_map<City, list<Theatre>> cityVsTheater;
        list<Theatre> allTheater;
    
    public:
        void addTheater(Theatre theater, City city){
            allTheater.push_back(theater);
            cityVsTheater[city].push_back(theater);
        }

        map<Theatre,list<Show>> getAllShow(Movie movie, City city){
            map<Theatre, list<Show>> theaterVsShow;
            list<Theatre> theatres = cityVsTheater[city];

            for(auto theatre : theatres){
                list<Show> movieShows;

                for(auto show : theatre.getShows()){
                    if(show.getMovie().getMovieId()==movie.getMovieId()){
                        movieShows.push_back(show);
                    }
                }

                if(!movieShows.empty()){
                    theaterVsShow[theatre] = movieShows;
                }
            }

            return theaterVsShow;
        }
};

class Payment{
    private:
        int id;
};

class Booking{
    private:
        Show show;
        list<Seat> bookedSeats;
        Payment payment;

    public:
        void setShow(Show show){
            this->show = show;
        }

        Show getShow(){
            return show;
        }

        void setBookedSeats(list<Seat> bookedSeats){
            this->bookedSeats = bookedSeats;
        }

        list<Seat> getBookedSeats(){
            return bookedSeats;
        }

        void setPayment(Payment payment){
            this->payment = payment;
        }

        Payment getPayment(){
            return payment;
        }
};

class BookMyShow{
    private:
        MoviesController movieController;
        TheaterController theaterController;

    public:
        BookMyShow(){

        }

        void createMovies(){
            Movie avenger;
            avenger.setMovieId(1);
            avenger.setMovieName("Avenger");
            avenger.setMovieDurationInMin(180);

            Movie starWars;
            starWars.setMovieId(2);
            starWars.setMovieName("Star Wars");
            starWars.setMovieDurationInMin(170);

            movieController.addMovie(avenger, City::Noida);
            movieController.addMovie(avenger, City::Agra);

            movieController.addMovie(starWars, City::Agra);
            movieController.addMovie(starWars, City::Noida);

        }
};


int main(){

    Movie m;
    m.setMovieId(5);

    cout<<m.getMovieId();


    return 0;
}
