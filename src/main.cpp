#include <iostream>
#include <string>
#include "cURLohmann.h"
#include "gui/imgui/imgui.h"
#include "gui/imgui/imgui_impl_dx9.h"
#include "gui/imgui/imgui_impl_win32.h"
#include <d3d9.h>

#include <iostream>
#include <string>
#include <tchar.h>
#include <random>
#include <time.h>
#include <ctime>
#include <thread>
#include <chrono>
// Close Buttons
bool theme_button = false;
bool dark_theme_button = true;
bool pvp_button = false;
bool survival_button = false;
bool scoreboard_button = false;
bool score_window_easy = false;
bool score_window_medium = false;
bool score_window_hard = false;
bool name_in = false;
bool loading_button = false;

int r1;
int r2;
int r3;
int k = 1;
int trues1 = 0;
int wrongs1 = 0;
int trues2 = 0;
int wrongs2 = 0;
int surv_wrongs = 0;
int surv_trues = 0;
bool game_pvp  = false;
bool game_pvp_show = false;
bool game_surv = false;
bool game_surv_show = false;
bool golden = false;
// Functions
void stylish();
void stylish_survival();
void timer(int sec);
std::vector <std::string> Q_A(std::string Categorey /*= "Japanese Anime & Manga"*/, std::string Dificulty /*= "easy"*/, std::string Mode = "PvP");

// Data
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main()
{
    // Create application window
// ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = {
        sizeof(wc),
        CS_CLASSDC,
        WndProc,
        0L,
        0L,
        GetModuleHandle(nullptr),
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        L"ImGui Example",
        nullptr
    };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(
        wc.lpszClassName, L"SEYED VERSE", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800,
        nullptr, nullptr, wc.hInstance, nullptr
    );

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    std::string font_path ="misc/Mikhak-Bold.ttf";
    ImFont* mainfont = io.Fonts->AddFontFromFileTTF(font_path.c_str(), 30);
    
    // Our state
    ImVec4 clear_color = ImVec4(40, 40, 40, 50);

    // Main loop

    // Buttons
    bool done = false;

    // Login Variables
    bool logged = false;
    static char passput[128];
    bool wrong_pass = false;
    bool login_pass = false;

    std::string Categorey;
    std::string Dificulty;
    std::string Mode;
    bool Inputs      = false;
    bool Inputs_surv = false;
    bool diff        = false;
    static char available_count_[128];
    static char name[128];
    static char price_[128];
    static char descript_[128];
    static char start_date_[128] = "\0";
    static char end_date_[128] = "\0";

    // ImGuiStyle new_dark;
    stylish();

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to
        // the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE
        // handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(400, 300));
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        if (login_pass == false)
        {
            if (ImGui::Begin(
                "##", NULL,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            ))
            {
                ImGui::SetCursorPos(ImVec2(100, 150));
                if (ImGui::Button("Start the journey",ImVec2(200,50)))
                {
                    logged = true;
                }
            }
            ImGui::End();
        }
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(600, 400));
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        // Main Page
        if (logged)
        {
            login_pass = true;
            if (ImGui::Begin(
                "Main Window", NULL,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            ))
            {
                ImGui::SetCursorPos(ImVec2(280, 40));
                ImGui::Text("Hello!");
                ImGui::SetCursorPos(ImVec2(185, 60));
                ImGui::Text("Wellcome to Quiz OF Seyeds");

                ImGui::SetCursorPos(ImVec2(20, 40));
                if (ImGui::Button("Theme", ImVec2(70, 40)))
                {
                    theme_button = true;
                }
                ImGui::SetCursorPos(ImVec2(40, 90));
                if (ImGui::Button("PvP", ImVec2(140, 80)))
                {
                    loading_button = true;
                }
                ImGui::SetCursorPos(ImVec2(420, 90));
                if (ImGui::Button("Survival", ImVec2(140, 80)))
                {
                    survival_button = true;
                }
                ImGui::SetCursorPos(ImVec2(160, 190));
                if (ImGui::Button("Score Board", ImVec2(280, 80)))
                {
                    scoreboard_button = true;
                }
            }ImGui::End();
        }

            // Themes
        ImGui::SetNextWindowSize(ImVec2(165, 120));
        if (theme_button)
        {
            if (ImGui::Begin(
                "Themes", &theme_button,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
            ))
            {
                if (dark_theme_button)
                {
                    if (ImGui::Button("Light", ImVec2(130, 50)))
                    {
                        ImGui::StyleColorsLight();
                        dark_theme_button = false;
                    }
                }
                else
                {
                    if (ImGui::Button("Dark", ImVec2(130, 50)))
                    {
                        stylish();
                        dark_theme_button = true;
                    }
                }
            }
            ImGui::End();
        }
///////// PVP
        if (loading_button)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if (ImGui::Begin("Loading . . . . . ", &loading_button, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                ImGui::Text("Usefull tips :");
                if (k == 1)
                {
                    ImGui::SetCursorPos(ImVec2(50, 100));
                    ImGui::Text("Answer 5 questions correctly to win");
                }
                else if (k == 2)
                {
                    ImGui::SetCursorPos(ImVec2(50, 100));
                    ImGui::Text("Click on the correct button to register");
                }
                else if (k == 3)
                {
                    ImGui::SetCursorPos(ImVec2(50, 100));
                    ImGui::Text("If you click on the wrong option, you will not get point");
                }
                else if (k == 4)
                {
                    ImGui::SetCursorPos(ImVec2(50, 100));
                    ImGui::Text("If you click on the right option, you will get point");
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(50, 100));
                    ImGui::Text("If you beat your opponent , you win");
                }
                ImGui::SetCursorPos(ImVec2(270, 230));
                Im_Spinner("##s", 20, 5, IM_COL32(255, 255, 255, 255));
                ImGui::SetCursorPos(ImVec2(50, 450));
                if (ImGui::Button("Next Tip"))
                {
                    k = (rand() % (5 - 1 + 1));
                }
                ImGui::SetCursorPos(ImVec2(440, 450));
                if (ImGui::Button("Continue >>"))
                {
                    pvp_button = true;
                    loading_button = false;
                }


            }ImGui::End();
        }
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(600, 500));
        if (pvp_button)
        {
            if (ImGui::Begin("PvP", &pvp_button,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                if (!game_pvp)
                {
                    if (!Inputs)
                    {
                        ImGui::Text("Be ready to start the battle");
                        if (ImGui::Button("Start", ImVec2(130, 50)))
                        {
                            Inputs = true;
                            srand(time(0));
                            ImGui::Text("Choose Categorey :");
                            r1 = (rand() % (32 - 9 + 1)) + 9;
                            r2 = (rand() % (32 - 9 + 1)) + 9;
                            r3 = (rand() % (32 - 9 + 1)) + 9;
                            if (r1 == r2)
                            {
                                r1 += 1;
                            }
                            if (r1 == r3)
                            {
                                r1 += 1;
                            }
                            if (r2 == r3)
                            {
                                r2 += 1;
                            }
                        }
                    }
                    if (Inputs)
                    {
                        if (!diff)
                        {
                            if (ImGui::Button(find_category(r1).c_str(), ImVec2(180, 50)))
                            {
                                Categorey = find_category(r1);
                                diff = true;
                            }
                            if (ImGui::Button(find_category(r2).c_str(), ImVec2(180, 50)))
                            {
                                Categorey = find_category(r2);
                                diff = true;
                            }
                            if (ImGui::Button(find_category(r3).c_str(), ImVec2(180, 50)))
                            {
                                Categorey = find_category(r3);
                                diff = true;
                            }
                        }
                        if (diff)
                        {
                            ImGui::Text("Choose Dificulty :");
                            if (ImGui::Button("Easy", ImVec2(130, 50)))
                            {
                                Dificulty = "easy";
                                game_pvp = true;
                            }
                            if (ImGui::Button("Medium", ImVec2(130, 50)))
                            {
                                Dificulty = "medium";
                                game_pvp = true;
                            }
                            if (ImGui::Button("Hard", ImVec2(130, 50)))
                            {
                                Dificulty = "hard";
                                game_pvp = true;
                                pvp_button = false;
                            }
                        }
                    }
                }

            }ImGui::End();
        }
        /*
        else
        {
            pvp_button = false;
            Inputs = false;
            diff = false;
            Dificulty = "";
            Categorey = "";
            r1 = NULL;
            r2 = NULL;
            r3 = NULL;
        }*/
        /*
        Dificulty = "";
        Categorey = "";
        r1 = NULL;
        r2 = NULL;
        r3 = NULL;*/
        if (game_pvp)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if (ImGui::Begin("PvP", &game_pvp, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                std::vector <std::string> vec;
                if (!golden)
                    vec = Q_A(Categorey, Dificulty, "pvp");
                if (golden)
                {

                    srand(time(0));
                    int r4 = (rand() % (32 - 9 + 1)) + 9;
                    Categorey = find_category(r4);
                    int r5 = (rand() % (3 - 1 + 1));
                    if (r5 == 1)
                        Dificulty = "easy";
                    else if (r5 == 2)
                        Dificulty = "medium";
                    else
                        Dificulty = "hard";
                    Q_A(Categorey, Dificulty, "Golden");
                }
                vec_saver(vec);
                game_pvp_show = true;
                game_pvp = false;
            }ImGui::End();
        }
        int nafar = 1;
        if (game_pvp_show)
        //for (int nafar = 1 ; nafar <= 2;++nafar)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(800, 500));
            if (ImGui::Begin("Choose the right answer", &game_pvp_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {

                std::fstream file;
                std::string question;
                file.open("Q_A.txt", std::ios::in);
                int t = 0;
                std::vector <std::string > vec1;
                std::vector <std::string > vect;
                while (!file.eof())
                {
                    time_t start = time(NULL);
                    time_t taken = time(NULL) + 0.5;
                    //while (start <= taken)
                    {
                        //ImGui::SetCursorPos(ImVec2(50, 50));
                        //ImGui::Text(("elapsed time : " + std::to_string(i)).c_str());
                        //start = time(NULL);
                        int a[4] = { 0,0,0,0 };
                        getline(file, question);
                            if (t  % 5 == 0)
                            {
                                t++;
                                ImGui::Text(question.c_str());

                            }
                            else if (t % 5 == 1)
                            {
                                t++;
                                if (ImGui::Button(question.c_str()))
                                {
                                    if (nafar == 1)
                                        trues1++;
                                    else
                                        trues2++;
                                }

                            }
                            else if (t % 5 == 2)
                            {
                                t++;
                                if (ImGui::Button(question.c_str()))
                                {
                                    if (nafar == 1)
                                        wrongs1++;
                                    else 
                                        wrongs2++;
                                }
                            }
                            else if (t % 5 == 3)
                            {
                                t++;
                                if (ImGui::Button(question.c_str()))
                                {
                                    if (nafar == 1)
                                        wrongs1++;
                                    else
                                        wrongs2++;
                                }
                            }
                            else if (t % 5 == 4)
                            {
                                t++;
                                if (ImGui::Button(question.c_str()))
                                {
                                    if (nafar == 1)
                                        wrongs1++;
                                    else
                                        wrongs2++;
                                }
                            }
                    }
                }
                /*
                if (trues1 == trues2)
                {
                    game_pvp = true;
                    golden = true;
                }*/
            }ImGui::End();
        }
///////// SURVIVAL
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(600, 500));
        if (survival_button)
        {
            if (!game_surv)
            {
                if (ImGui::Begin("Survival", &survival_button,
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
                {
                    if (!Inputs_surv)
                    {
                        ImGui::Text("Welcome to survival\nIf you survive you earn your wisdom");
                        if (ImGui::Button("Start", ImVec2(130, 50)))
                        {
                            Inputs_surv = true;
                            stylish_survival();
                        }
                    }
                    if (Inputs_surv)
                    {
                        if (!name_in)
                        {
                            ImGui::Text("Enter your Seyedi nick name :");
                            name_in = ImGui::InputText("##", name, sizeof(name), ImGuiInputTextFlags_EnterReturnsTrue);
                        }
                        if (name_in)
                        {
                            ImGui::Text("Choose Dificulty :");
                            if (ImGui::Button("Easy", ImVec2(130, 50)))
                            {
                                Dificulty = "easy";
                                game_surv = true;
                            }
                            if (ImGui::Button("Medium", ImVec2(130, 50)))
                            {
                                Dificulty = "medium";
                                game_surv = true;
                            }
                            if (ImGui::Button("Hard", ImVec2(130, 50)))
                            {
                                Dificulty = "hard";
                                game_surv = true;
                            }
                        }
                    }
                }ImGui::End();
            }
            if (game_surv)
            {
                if (ImGui::Begin("Survaival", &game_surv,
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
                {
                    srand(time(0));
                    int r4 = (rand() % (32 - 9 + 1)) + 9;
                    Categorey = find_category(r4);
                    std::vector <std::string> vec = Q_A(Categorey, Dificulty, "Survival");
                    vec_saver(vec);
                    game_surv_show = true;
                    game_surv = false;
                }ImGui::End();
            }
        }
        if (game_surv_show)
        {
            if (ImGui::Begin("Choose the right answer", &game_surv_show,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                while (surv_wrongs <= 3)
                {
                    std::fstream file;
                    std::string question;
                    file.open("Q_A.txt", std::ios::in);
                    int t = 0;
                    while (!file.eof())
                    {
                        t++;
                        getline(file, question);
                        if (t % 5 == 0)
                        {
                            t++;
                            ImGui::Text(question.c_str());
                        }
                        else if (t % 5 == 1)
                        {
                            t++;
                            if (ImGui::Button(question.c_str()))
                            {
                                surv_trues++;
                            }

                        }
                        else if (t % 5 == 2)
                        {
                            t++;
                            if (ImGui::Button(question.c_str()))
                            {
                                surv_wrongs++;
                            }
                        }
                        else if (t % 5 == 3)
                        {
                            t++;
                            if (ImGui::Button(question.c_str()))
                            {
                                surv_wrongs++;
                            }
                        }
                        else if (t % 5 == 4)
                        {
                            t++;
                            if (ImGui::Button(question.c_str()))
                            {
                                surv_wrongs++;
                            }
                        }

                    }
                }
                score_saver(name, surv_trues, Dificulty);
                surv_wrongs = 0;
                surv_trues = 0;
            }ImGui::End();
        }
        /*else
        {
            survival_button = false;
            Inputs_surv = false;
            game_surv = false;
            Dificulty = "";
            Categorey = "";
            r1 = NULL;
            r2 = NULL;
            r3 = NULL;
            stylish();
        }*/
        if (scoreboard_button)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if(ImGui::Begin("Score Board", &scoreboard_button,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                ImGui::Text("Choose Dificulty :");
                if (ImGui::Button("Easy", ImVec2(130, 50)))
                {
                    score_window_easy = true;
                }
                else if (ImGui::Button("Medium", ImVec2(130, 50)))
                {
                    score_window_medium = true;
                }
                else if (ImGui::Button("Hard", ImVec2(130, 50)))
                {
                    score_window_hard = true;
                }
            }ImGui::End();
        }
        if (score_window_easy)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if (ImGui::Begin("Score Board Easy", &score_window_easy,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                score_reader("easy");
            }ImGui::End();
        }
        if (score_window_medium)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if (ImGui::Begin("Score Board Medium", &score_window_medium,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                score_reader("medium");
            }ImGui::End();
        }
        if (score_window_hard)
        {
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 500));
            if (ImGui::Begin("Score Board Hard", &score_window_hard,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
            {
                score_reader("hard");
            }ImGui::End();
        }
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA(
            (int)(clear_color.x * clear_color.w * 255.0f),
            (int)(clear_color.y * clear_color.w * 255.0f),
            (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f)
        );
        g_pd3dDevice->Clear(
            0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0
        );
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST &&
            g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}


// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat =
        D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if
    // needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
    // g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   //
    // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice
    ) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = nullptr;
    }
    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = nullptr;
    }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}


void stylish()
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 5.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 3.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.3f, 0.0f, 1.0f, 0.80f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}
void stylish_survival()
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::SetWindowFontScale(1);
    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 0.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 0.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.0f, 0.88f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.0f, 0.0f, 0.4f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.0f, 0.0f, 0.8f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

std::vector < std::string> Q_A(std::string Categorey ,std::string Dificulty ,std::string Mode)
{
    {
        int t = tedad_soal(Mode);
        std::string url = URL_maker(Dificulty, Categorey, t);
        std::vector <std::string> vec = curler(url, t);
        return vec;
    }
}
void timer(int seconds)
{
    ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::SetCursorPos(ImVec2((size.x - 40) / 2, (size.y - 40) / 2));
    Im_Spinner("##s", 20, 5, IM_COL32(255, 255, 255, 255));
    Sleep(seconds * 1000);
}