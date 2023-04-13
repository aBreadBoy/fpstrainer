#include "raylib.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Clicking Maniac");
    
    // Load the sound effect
    Sound buttonSound = LoadSound("pianosong.ogg");

    int score = 0;

    SetTargetFPS(60); // Set the framerate

    // Define the circle
    float circleX = GetRandomValue(50, screenWidth - 50);
    float circleY = GetRandomValue(50, screenHeight - 50);
    const float circleRadius = 30.0f;
    const Color circleColor = BROWN;

    bool isPlaying = false;
    bool isQuitting = false;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (!isPlaying)
        {
            // Update the menu screen
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Check if the mouse click is inside the "Play" button
                Rectangle playButton = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 40 };
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, playButton))
                {
                    isPlaying = true;
                    PlaySound(buttonSound);
                }

                // Check if the mouse click is inside the "Quit" button
                Rectangle quitButton = { screenWidth / 2 - 100, screenHeight / 2 + 50, 200, 40 };
                if (CheckCollisionPointRec(mousePosition, quitButton))
                {
                    isQuitting = true;
                }
            }

            // Draw the menu screen
            BeginDrawing();

            ClearBackground(BEIGE);

            // Draw the "Play" button
            Rectangle playButton = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 40 };
            DrawRectangleRec(playButton, LIGHTGRAY);
            DrawText("Play", screenWidth / 2 - MeasureText("Play", 20) / 2, screenHeight / 2 - 35, 20, BLACK);

            // Draw the "Quit" button
            Rectangle quitButton = { screenWidth / 2 - 100, screenHeight / 2 + 50, 200, 40 };
            DrawRectangleRec(quitButton, LIGHTGRAY);
            DrawText("Quit", screenWidth / 2 - MeasureText("Quit", 20) / 2, screenHeight / 2 + 65, 20, BLACK);
            
            // Draw The Title Text
            DrawText("Clicking Maniac", screenWidth / 2 - MeasureText("Clicking Maniac", 50) / 2, screenHeight / 3 + -120, 50, BLACK);

            EndDrawing();
        }
        else
        {
            // Update the game
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Check if the mouse click is inside the circle
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointCircle(mousePosition, (Vector2){ circleX, circleY }, circleRadius))
                {
                    // Add 1 to the score and move the circle to a new position
                    score++;
                    circleX = GetRandomValue(50, screenWidth - 50);
                    circleY = GetRandomValue(50, screenHeight - 50);
                }
            }

            // Draw the game
            BeginDrawing();

            ClearBackground(BEIGE);

            // Draw the circle
            DrawCircleV((Vector2){ circleX, circleY }, circleRadius, circleColor);

            // Draw the score
            DrawText(TextFormat("Score: %d", score), 20, 20, 20, BLACK);

        EndDrawing();
    }

    if (isQuitting)
    {
        break;
    }
}

// De-Initialization
CloseWindow();

return 0;
}