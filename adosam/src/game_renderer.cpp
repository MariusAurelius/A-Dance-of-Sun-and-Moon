#include "game_renderer.h"

GameRenderer::GameRenderer() 
:img_tile_path_("../assets/tiles_img/"), img_extension_(".png") {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize Video! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    if (TTF_Init() < 0) {
        std::cerr << "SDL could not initialize SDL_ttf! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_VideoQuit();
        SDL_Quit();
    }

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        std::cerr<< "Could not open SDL_MIXER " << Mix_GetError();
        SDL_VideoQuit();
        TTF_Quit();
        SDL_Quit();
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_VideoQuit();
        TTF_Quit();
        SDL_Quit();
    }

    displaymode_ = new SDL_DisplayMode;
    if (SDL_GetDesktopDisplayMode(0, displaymode_) != 0) {
        std::cerr << "SDL could not get display information! SDL_Error: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    window_ = SDL_CreateWindow("ADOFAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displaymode_->w, displaymode_->h, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL);
    if(window_ == nullptr)
    {
        std::cerr << "SDL could not create the window! SDL_Error: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
    
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(renderer_ == nullptr)
    {
        std::cerr << "SDL could not create the renderer! SDL_Error: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_VideoQuit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }
    
    font_ = TTF_OpenFont("../assets/font.ttf", 24);
    if(font_ == nullptr){
        std::cerr << "SDL could not open the font! SDL_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Color Blue = {0, 0, 255};
    score_surface_ = TTF_RenderText_Solid(font_, "lol", Blue);
    score_texture_ = SDL_CreateTextureFromSurface(renderer_, score_surface_);
    score_rect_ = new SDL_Rect;
    score_rect_ -> x = 200;
    score_rect_ -> y = 200;
    score_rect_ -> w = 500;
    score_rect_ -> h = 500;

    menu_background_= new Image(renderer_, "../assets/menu.png", 0, 0, displaymode_ -> w, displaymode_ -> h);
    background_ = new Image(renderer_, "../assets/background.png", 0, 0, displaymode_ -> w, displaymode_ -> h);
    level_ = new Level(renderer_, "../assets/tiles_img2/", ".png", "assets/maps/map1/", displaymode_, 150, 0);
    quit_ = new Button(renderer_, "../assets/quit.png", 5, 5, 50, 50);
}

GameRenderer::~GameRenderer(){
    delete menu_background_;
    menu_background_ = nullptr;

    delete background_;
    background_ = nullptr;

    delete quit_;
    quit_ = nullptr;

    delete level_;
    level_ = nullptr;

    delete displaymode_;
    displaymode_ = nullptr;

    delete score_rect_;
    score_rect_ = nullptr;

    SDL_FreeSurface(score_surface_);
    score_surface_ = nullptr;

    SDL_DestroyTexture(score_texture_);
    score_texture_ = nullptr;

    TTF_CloseFont(font_);
    font_ = nullptr;

    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;

    SDL_DestroyWindow(window_);
    window_ = nullptr;

    Mix_CloseAudio();
    SDL_VideoQuit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


void GameRenderer::IfKeyDown(){
    level_ -> PlayerGoNextTile();
}

bool GameRenderer::IfMouseButtonDown(std::string button_name, SDL_Event event){
    if(button_name == "quit"){
        return quit_ -> CheckIfClicked(event);
    }
    
    return false;
}

void GameRenderer::Update(){
    level_ -> Update();
}

void GameRenderer::Render(){
    background_ -> Render();
    level_ -> Render();
    if(SDL_RenderCopy(renderer_, score_texture_, nullptr, score_rect_) != 0){
        std::cerr << "Error rendering Score: " << SDL_GetError() << std::endl;
    }
    quit_ -> Render();
}

void GameRenderer::Start(){
    level_ -> Start();
}

SDL_Renderer* GameRenderer::GetRenderer(){
    return renderer_;
}