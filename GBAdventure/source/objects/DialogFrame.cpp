#include "objects/DialogFrame.hpp"

//                      ---- Construction ----

objects::DialogFrame::DialogFrame() { DialogFrame::initialize_static_members(); }

objects::DialogFrame::DialogFrame(int x, int y, int width, int height)
    : DialogFrame()
{
    DialogFrame::set_area(x, y, width, height);
}

//                      ---- Public Functions ----

void objects::DialogFrame::set_area(int x, int y, int width, int height) noexcept
{
    m_x      = x;
    m_y      = y;
    m_width  = width;
    m_height = height;
}

void objects::DialogFrame::render(sdl3::Renderer &renderer)
{

    // Top.
    sm_dialogTexture->render_part(m_x, m_y, 0, 0, 8, 8);
    sm_dialogTexture->render_part_stretched(m_x + 8, m_y, m_width - 16, 8, 8, 0, 8, 8);
    sm_dialogTexture->render_part((m_x + m_width) - 8, m_y, 16, 0, 8, 8);

    // Mid.
    sm_dialogTexture->render_part_stretched(m_x, m_y + 8, 8, m_height - 16, 0, 8, 8, 8);
    sm_dialogTexture->render_part_stretched(m_x + 8, m_y + 8, m_width - 16, m_height - 16, 8, 8, 8, 8);
    sm_dialogTexture->render_part_stretched(m_x + m_width - 8, m_y + 8, 8, m_height - 16, 16, 8, 8, 8);

    // Bottom.
    sm_dialogTexture->render_part(m_x, m_y + m_height - 8, 0, 16, 8, 8);
    sm_dialogTexture->render_part_stretched(m_x + 8, m_y + m_height - 8, m_width - 16, 8, 8, 16, 8, 8);
    sm_dialogTexture->render_part(m_x + m_width - 8, m_y + m_height - 8, 16, 16, 8, 8);
}

//                      ---- Private Functions ----

void objects::DialogFrame::initialize_static_members()
{
    // Path to the frame texture to load.
    static constexpr std::string_view FRAME_TEXTURE_PATH = "./assets/FrameA.png";

    if (sm_dialogTexture) { return; }

    // Load texture.
    sm_dialogTexture = sdl3::TextureManager::load_resource(FRAME_TEXTURE_PATH, FRAME_TEXTURE_PATH);
    // Make sure it's pixelated.
    sm_dialogTexture->set_scale_mode(SDL_SCALEMODE_NEAREST);
}