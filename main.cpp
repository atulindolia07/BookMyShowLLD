#include<iostream>
#include<map>
#include<list>
#include <string>
#include <algorithm>

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
        map<City,list<Movie>> moviesListByCity;
        list<Movie> allMovies;

    public:

        MoviesController(map<City,list<Movie>> &CityVsMovie, list<Movie> &allMovies){
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

        Movie getMovieByName(string name){
            for(auto movie : allMovies){
                if(movie.getMovieName()==name){
                    return movie;
                }
            }

            Movie movie;
            return movie;
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

        Screen getScreen(){
            return screen;
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

        string getTheaterAddress(){
            return address;
        }

        void setCity(City city){
            this->city = city;
        }

        City getCity(){
            return this->city;
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

        list<Screen> getScreens(){
            return screen;
        }
};

class TheaterController{
    private:
        map<City, list<Theatre>> cityVsTheater;
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

        void initialize(){
            createMovies();
            createTheater();
        }

        void createBooking(City userCity, string movieName){
            //search movie by name and city
            list<Movie> moviesList = movieController.getMovieByCity(userCity);

            Movie interestedMovie;
            //getting interested movie
            for(auto movie : moviesList){
                if(movie.getMovieName()==movieName){
                    interestedMovie = movie;
                    break;
                }
            }

            //list of all theater in which interested movie
            map<Theatre,list<Show>> listOfShows = theaterController.getAllShow(interestedMovie,userCity);
            Show interestedShow;

            for(auto it : listOfShows){
                if(!it.second.empty()){
                    interestedShow = it.second.front();
                }

                break;
            }

            int seatIdRequiredToBook = 30;

            list<int> listOfBookedSeats = interestedShow.getListOfSeatsBooked();

            auto it = std::find(listOfBookedSeats.begin(),listOfBookedSeats.end(),seatIdRequiredToBook);

            if(it==listOfBookedSeats.end()){
                listOfBookedSeats.push_back(seatIdRequiredToBook);

                Booking booking;

                list<Seat> myBookedSeats;
                for(Seat seat : interestedShow.getScreen().getSeats()){
                    if(seat.getSeatId()==seatIdRequiredToBook){
                        myBookedSeats.push_back(seat);
                    }
                }

                booking.setBookedSeats(myBookedSeats);
                booking.setShow(interestedShow);
            } else{
                std::cout<<"Seat already booked!"<<std::endl;
                return;
            }

            std::cout<<"Booking Successful"<<std::endl;

        }

        void createTheater(){
            Movie avenger = movieController.getMovieByName("Avenger");
            Movie starWars = movieController.getMovieByName("Star Wars");

            Theatre shreeTalkies;
            shreeTalkies.setCity(City::Agra);
            shreeTalkies.setTheaterId(1);
            shreeTalkies.setScreens(createScreens());
            list<Show> shreeShows;

            Show shreeFirstShow = createShows(1, avenger, shreeTalkies.getScreens().front(), 9);
            Show shreeSecondShow = createShows(2, starWars, shreeTalkies.getScreens().front(), 13);

            shreeShows.push_back(shreeFirstShow);
            shreeShows.push_back(shreeSecondShow);
            shreeTalkies.setShows(shreeShows);

            Theatre pvrTheater;
            pvrTheater.setCity(City::Noida);
            pvrTheater.setTheaterId(1);
            pvrTheater.setScreens(createScreens());
            list<Show> pvrShows;

            Show pvrFirstShow = createShows(1, avenger, pvrTheater.getScreens().front(), 9);
            Show pvrSecondShow = createShows(2, starWars, pvrTheater.getScreens().front(), 13);

            pvrShows.push_back(pvrFirstShow);
            pvrShows.push_back(pvrSecondShow);
            pvrTheater.setShows(pvrShows);


            theaterController.addTheater(pvrTheater, City::Noida);
            theaterController.addTheater(shreeTalkies, City::Agra);

        }

        list<Seat> createSeats(){
            list<Seat> seats;

            //silver seats
            for(int i=0;i<40;i++){
                Seat seat;
                seat.setSeatId(i);
                seat.setSeatCategory(SeatCategory::Silver);
                seats.push_back(seat);
            }

            //gold seats
            for(int i=40;i<70;i++){
                Seat seat;
                seat.setSeatId(i);
                seat.setSeatCategory(SeatCategory::Gold);
                seats.push_back(seat);
            }

            //platinum seats
            for(int i=70;i<100;i++){
                Seat seat;
                seat.setSeatId(i);
                seat.setSeatCategory(SeatCategory::Platinum);
                seats.push_back(seat);
            }

            return seats;
        }

        Show createShows(int showId, Movie movie, Screen screen, int showStartTime){
            Show show;
            show.setShowId(showId);
            show.setMovie(movie);
            show.setScreen(screen);
            show.setStartTime(showStartTime);

            return show;
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

        list<Screen> createScreens(){
            list<Screen> screens;

            Screen scr;
            scr.setScreenId(1);
            list<Seat> seats;
            scr.setSeats(seats);

            return screens;
        }
};


int main(){

    BookMyShow bookMyShow;
    bookMyShow.initialize();
    bookMyShow.createBooking(City::Agra,"Avenger");


    return 0;
}
