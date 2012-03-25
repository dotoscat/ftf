var screen;
var images;

var currentscene;

function load(){
    screen = document.getElementById("screen").getContext('2d');
    images = new Array();
    setInterval(game_run, 1000/60);
}

function draw_text(text, color, x, y){
    screen.fillStyle = color;
    screen.fillText(text, x, y);
}

function Screen(){
    this.title = "Free For Fall";
    this.Run = function(){
        draw_text(this.title, "#00FF00", 64, 64);
    }
}

currentscene = new Screen();

function game_run(){
    screen.clearRect(0, 0, 640, 480);
    currentscene.Run();
}
