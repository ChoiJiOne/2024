using System;
using SDL2;


/**
 * @brief 렌더링을 수행하는 싱글턴 클래스입니다.
 */
class RenderManager
{
    /**
     * @brief 렌더링을 수행하는 렌더 매니저의 인스턴스를 얻습니다.
     * 
     * @return 렌더 매니저 인스턴스를 반환합니다.
     */
    public static RenderManager Get()
    {
        if(renderManager_ == null)
        {
            renderManager_ = new RenderManager();
        }

        return renderManager_;
    }


    /**
     * @brief 렌더 매니저를 초기화합니다.
     * 
     * @param window 렌더러를 생성할 때 참조할 SDL 윈도우 포인터입니다.
     * @param bIsAccelerated 렌더러의 하드웨어 가속 여부입니다. 기본 값은 true입니다.
     * @param bIsSync 렌더러의 수직 동기화 여부입니다. 기본 값은 true입니다.
     * 
     * @throw 초기화에 실패하면 예외를 던집니다.
     */
    public void Setup(IntPtr window, bool bIsAccelerated = true, bool bIsSync = true)
    {
        if (bIsSetup_) return;

        int Flags = 0;
        Flags |= (bIsAccelerated ? (int)(SDL.SDL_RendererFlags.SDL_RENDERER_ACCELERATED) : 0);
        Flags |= (bIsSync ? (int)(SDL.SDL_RendererFlags.SDL_RENDERER_PRESENTVSYNC) : 0);

        renderer_ = SDL.SDL_CreateRenderer(window, -1, (SDL.SDL_RendererFlags)(Flags));

        if (renderer_ == IntPtr.Zero)
        {
            throw new Exception("failed to create renderer...");
        }

        bIsSetup_ = true;
    }


    /**
     * @brief 렌더 매니저 내의 리소스를 명시적으로 정리합니다.
     */
    public void Cleanup()
    {
        SDL.SDL_DestroyRenderer(renderer_);

        bIsSetup_ = false;
    }


    /**
     * @brief SDL 렌더러의 포인터를 얻습니다.
     * 
     * @return SDL 렌더러의 포인터 값을 반환합니다.
     */
    public IntPtr GetRendererPtr()
    {
        return renderer_;
    }


    /**
     * @brief 백버퍼를 초기화합니다.
     * 
     * @param color 초기화 할 RGBA 색상입니다.
     * 
     * @throw 백버퍼를 초기화하는 데 실패하면 예외를 던집니다.
     */
    public void Clear(Color color)
    {
        SetDrawColor(color);

        if (SDL.SDL_RenderClear(renderer_) != 0)
        {
            throw new Exception("failed to clear back buffer...");
        }
    }


    /**
     * @brief 백버퍼와 프론트 버퍼를 스왑합니다.
     */
    public void Present()
    {
        SDL.SDL_RenderPresent(renderer_);
    }


    /**
     * @brief 백버퍼에 텍스처를 그립니다.
     * 
     * @param texture 백버퍼에 그릴 텍스처 리소스입니다.
     * @param center 텍스처의 화면 상 중심 좌표입니다.
     * @param width 텍스처의 가로 크기입니다.
     * @param height 텍스처의 세로 크기입니다.
     * @param rotate 텍스처의 회전 각도 값입니다. 기준은 육십분법이고 기본 값은 0.0입니다.
     * 
     * @throws 텍스처를 백버퍼에 그리는 데 실패하면 예외를 던집니다.
     */
    public void DrawTexture(ref Texture texture, Vector2<float> center, float width, float height, float rotate = 0.0f)
    {
        SDL.SDL_Rect rect;
        rect.x = (int)(center.x - width / 2.0f);
        rect.y = (int)(center.y - height / 2.0f);
        rect.w = (int)(width);
        rect.h = (int)(height);

        SDL.SDL_Point point;
        point.x = (int)(center.x);
        point.y = (int)(center.y);

        if (SDL.SDL_RenderCopyEx(
            renderer_, 
            texture.Resource, 
            IntPtr.Zero, 
            ref rect, 
            rotate, 
            ref point, 
            SDL.SDL_RendererFlip.SDL_FLIP_NONE) != 0)
        {
            throw new Exception("failed to draw texture in back buffer...");
        }
    }


    /**
     * @brief 가로로 움직이는 텍스처를 백버퍼에 그립니다.
     * 
     * @note 텍스처 분할 비율은 다음과 같습니다.
     * 
     * ┌────────────┬──────────────────┐
     * │            │                  │
     * │            │                  │
     * │            │                  │
     * │            │                  │
     * │ 1.0f - rate│       rate       │
     * │            │                  │
     * │            │                  │
     * │            │                  │
     * └────────────┴──────────────────┘
     * 
     * @param texture 백버퍼에 그릴 텍스처 리소스입니다.
     * @param center 텍스처의 화면 상 중심 좌표입니다.
     * @param width 텍스처의 가로 크기입니다.
     * @param height 텍스처의 세로 크기입니다.
     * @param rate 텍스처 분할 비율입니다.
     */
    public void DrawHorizonScrollingTexture(ref Texture texture, Vector2<float> center, float width, float height, float rate)
    {
        float texWidth = texture.Width;
        float texHeight = texture.Height;

        SDL.SDL_Rect leftSrcRect;
        leftSrcRect.x = (int)(texWidth * rate);
        leftSrcRect.y = 0;
        leftSrcRect.w = (int)(texWidth * (1.0f - rate));
        leftSrcRect.h = (int)texHeight;

        SDL.SDL_Rect leftDstRect;
        leftDstRect.x = (int)(center.x - width / 2.0f);
        leftDstRect.y = (int)(center.y - height / 2.0f);
        leftDstRect.w = (int)(width * (1.0f - rate));
        leftDstRect.h = (int)(height);

        if(SDL.SDL_RenderCopy(renderer_, texture.Resource, ref leftSrcRect, ref leftDstRect) != 0)
        {
            throw new Exception("failed to draw horizon scrolling left texture...");
        }

        SDL.SDL_Rect rightSrcRect;
        rightSrcRect.x = 0;
        rightSrcRect.y = 0;
        rightSrcRect.w = (int)(texWidth * rate);
        rightSrcRect.h = (int)texHeight;

        SDL.SDL_Rect rightDstRect;
        rightDstRect.x = (int)(center.x - width / 2.0f + width * (1.0f - rate));
        rightDstRect.y = (int)(center.y - height / 2.0f);
        rightDstRect.w = (int)(width * rate);
        rightDstRect.h = (int)(height);

        if(SDL.SDL_RenderCopy(renderer_, texture.Resource, ref rightSrcRect, ref rightDstRect) != 0)
        {
            throw new Exception("failed to draw horizon scrolling right texture...");
        }
    }


    /**
     * @brief 세로로 움직이는 텍스처를 백버퍼에 그립니다.
     * 
     * @note 텍스처 분할 비율은 다음과 같습니다.
     * 
     * ┌─────────────────────────────┐
     * │                             │
     * │                             │
     * │         1.0f - rate         │
     * │                             │
     * ├─────────────────────────────┤
     * │                             │
     * │            rate             │
     * │                             │
     * └─────────────────────────────┘
     * 
     * @param texture 백버퍼에 그릴 텍스처 리소스입니다.
     * @param center 텍스처의 화면 상 중심 좌표입니다.
     * @param width 텍스처의 가로 크기입니다.
     * @param height 텍스처의 세로 크기입니다.
     * @param rate 텍스처 분할 비율입니다.
     */
    public void DrawVerticalScrollingTexture(ref Texture texture, Vector2<float> center, float width, float height, float rate)
    {
        float texWidth = texture.Width;
        float texHeight = texture.Height;

        SDL.SDL_Rect topSrcRect;
        topSrcRect.x = 0;
        topSrcRect.y = (int)(texHeight * rate);
        topSrcRect.w = (int)texWidth;
        topSrcRect.h = (int)(texHeight * (1.0f - rate));

        SDL.SDL_Rect topDstRect;
        topDstRect.x = (int)(center.x - width / 2.0f);
        topDstRect.y = (int)(center.y - height / 2.0f);
        topDstRect.w = (int)width;
        topDstRect.h = (int)(height * (1.0f - rate));

        if (SDL.SDL_RenderCopy(renderer_, texture.Resource, ref topSrcRect, ref topDstRect) != 0)
        {
            throw new Exception("failed to draw horizon scrolling top texture...");
        }

        SDL.SDL_Rect bottomSrcRect;
        bottomSrcRect.x = 0;
        bottomSrcRect.y = 0;
        bottomSrcRect.w = (int)texWidth;
        bottomSrcRect.h = (int)(texHeight * rate);

        SDL.SDL_Rect bottomDstRect;
        bottomDstRect.x = (int)(center.x - width / 2.0f);
        bottomDstRect.y = (int)(center.y - height / 2.0f + height * (1.0f - rate));
        bottomDstRect.w = (int)width;
        bottomDstRect.h = (int)(height * rate);

        if (SDL.SDL_RenderCopy(renderer_, texture.Resource, ref bottomSrcRect, ref bottomDstRect) != 0)
        {
            throw new Exception("failed to draw horizon scrolling bottom texture...");
        }
    }


    /**
     * @brief 텍스트를 백버퍼에 그립니다.
     * 
     * @param font 텍스트의 폰트 정보입니다.
     * @param text 백버퍼에 그릴 텍스트입니다.
     * @param center 텍스트의 중심 좌표입니다.
     * @param color 텍스트의 색상입니다.
     */
    public void DrawText(ref TTFont font, string text, Vector2<float> center, Color color)
    {
        if(!font.MeasureText(text, out int width, out int height))
        {
            return;
        }

        float x = center.x - (float)width / 2.0f;
        float y = center.y - (float)height / 2.0f;
        IntPtr textureAtlas = font.TextureAtlas;

        color.ConvertToByte(out byte r, out byte g, out byte b, out byte a);

        if (SDL.SDL_SetTextureAlphaMod(textureAtlas, a) != 0)
        {
            throw new Exception("failed to set texture atlas alpha mode...");
        }

        if(SDL.SDL_SetTextureColorMod(textureAtlas, r, g, b) != 0)
        {
            throw new Exception("failed to set texture atlas color mode...");
        }

        for (int index = 0; index < text.Length; ++index)
        {
            Glyph glyph = font.GetGlyph((ushort)text[index]);

            SDL.SDL_Rect SrcRect;
            SrcRect.x = glyph.x;
            SrcRect.y = glyph.y;
            SrcRect.w = glyph.width;
            SrcRect.h = glyph.height;

            SDL.SDL_Rect DstRect;
            DstRect.x = (int)x;
            DstRect.y = (int)y - glyph.yoffset;
            DstRect.w = glyph.width;
            DstRect.h = glyph.height;

            if (SDL.SDL_RenderCopy(renderer_, textureAtlas, ref SrcRect, ref DstRect) != 0)
            {
                throw new Exception("failed to draw texture atlas...");
            }

            x += glyph.xadvance;
        }
    }


    /**
     * @brief 생성자는 외부에서 호출할 수 없도록 감춤니다.
     */
    private RenderManager() { }


    /**
     * @brief SDL 렌더링 컨텍스트에 색상을 설정합니다.
     * 
     * @param color SDL 렌더링 컨텍스트에 설정할 색상입니다.
     * 
     * @throws 색상 설정에 실패하면 예외를 던집니다.
     */
    private void SetDrawColor(Color color)
    {
        color.ConvertToByte(out byte r, out byte g, out byte b, out byte a);

        if(SDL.SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
        {
            throw new Exception("failed to set draw color...");
        }
    }


    /**
     * @brief 렌더 매니저가 초기화된 적이 있는지 확인합니다.
     */
    private bool bIsSetup_ = false;


    /**
     * @brief SDL 렌더러의 포인터입니다.
     */
    private IntPtr renderer_;


    /**
     * @brief 렌더링을 수행하는 렌더 매니저의 인스턴스입니다.
     */
    private static RenderManager renderManager_;
}