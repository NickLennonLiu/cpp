/*
while(true){
    if(keyPressed()) {
        snake.chgDirection(dirInput);
    }
    if(snake.growStatus()==0)
        board.removeSnakePart(snake.retract());
    else 
        snake.grow();
    status = board.detect(snake.move());
    if(status == "apple_eaten"){
        ...
    }
    else if (status == "wall_hit") {
        ...
    }
    else if (status == "self_hit") {
        ...
    }
    else {      // normal
        ...
    }
}
*/