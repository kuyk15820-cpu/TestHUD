#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / IM_PI) )
#define DEG2RAD( x ) ( (float)(x) * (float)(IM_PI / 180.f) )


static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x + rhs, lhs.y + rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x - rhs, lhs.y - rhs); }
static inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
static inline ImVec4  operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4  operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4  operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }


template <typename T>
inline T clamp(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

inline float lerp(float a, float b, float f) {
	return clamp<float>(a + f * (b - a),a > b ? b : a,a > b ? a : b);
}

ImColor CalculateHealthColor(int health, int max_health) {
    float healthPercent = static_cast<float>(health) / max_health;
    float red = 255 * (1 - healthPercent); // Đỏ tăng dần khi máu giảm
    float green = 255 * healthPercent;      // Xanh lá cây giảm dần khi máu giảm
    return ImColor(static_cast<int>(red), static_cast<int>(green), 0);
}


ImVec2 calcTextSize(std::string text, double scaling) {
  return ImGui::CalcTextSize(text.c_str());
}

inline ImColor collerp(ImColor a, ImColor b, float f) {
  return {a.Value.x + f * (b.Value.x - a.Value.x), a.Value.y + f * (b.Value.y - a.Value.y), a.Value.z + f * (b.Value.z - a.Value.z), a.Value.w + f * (b.Value.w - a.Value.w)};
}

void DrawText2(float fontSize, ImVec2 position, ImColor Color, const char *text)
{
    std::string distanceText = "[" +std::string(text) + "M]";
    
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();

    draw_list->AddText(_espFont, fontSize, position, Color, distanceText.c_str());
}

void VectorAnglesRadar(Vector3 &forward, Vector3 &angles) {
  if (forward.x == 0.f && forward.y == 0.f) {
    angles.x = forward.z > 0.f ? -90.f : 90.f;
    angles.y = 0.f;
  } else {
    angles.x = RAD2DEG(atan2(-forward.z, forward.Magnitude(forward)));
    angles.y = RAD2DEG(atan2(forward.y, forward.x));
  }
  angles.z = 0.f;
}

void playerTriangle(ImVec2 Pos) {
  Vector3 angle = Vector3::zero();
  Vector3 forward =
      Vector3((float)(kWidth / 2) - Pos.x, (float)(kHeight / 2) - Pos.y, 0.0f);

  VectorAnglesRadar(forward, angle);

  const auto angle_yaw_rad = DEG2RAD(angle.y + 180.f);
  const auto new_point_x = (kWidth / 2) + (35.5) / 2 * 8 * cosf(angle_yaw_rad);
  const auto new_point_y = (kHeight / 2) + (35.5) / 2 * 8 * sinf(angle_yaw_rad);

  std::array<Vector3, 3> points{
      Vector3(new_point_x - ((90) / 4 + 3.5f) / 2,
              new_point_y - ((35.5) / 4 + 3.5f) / 2, 0.f),
      Vector3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y, 0.f),
      Vector3(new_point_x - ((90) / 4 + 3.5f) / 2,
              new_point_y + ((35.5) / 4 + 3.5f) / 2, 0.f)};

  RotateTriangle(points, angle.y + 180.f);

  ImU32 _Color = IM_COL32(0, 255, 0, 255);

  ImGui::GetForegroundDrawList()->AddTriangle(
      ImVec2(points.at(0).x, points.at(0).y),
      ImVec2(points.at(1).x, points.at(1).y),
      ImVec2(points.at(2).x, points.at(2).y), _Color, 1.0f);
}

void RotateTriangle(std::array<Vector3, 3> &points, float rotation) {
  const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
  for (auto &point : points) {
    point = point - points_center;
    const auto temp_x = point.x;
    const auto temp_y = point.y;
    const auto theta = DEG2RAD(rotation);
    const auto c = cosf(theta);
    const auto s = sinf(theta);
    point.x = temp_x * c - temp_y * s;
    point.y = temp_x * s + temp_y * c;
    point = point + points_center;
  }
}


void Draw3DBox(Vector3 position, Vector3 size, bool &checker) {
    auto cam = get_camera();
    if (!cam) return;

    Vector3 min = position - size / 2;
    Vector3 max = position + size / 2;

    Vector3 vertices[8];
    vertices[0] = { min.x, min.y, min.z };
    vertices[1] = { min.x, max.y, min.z };
    vertices[2] = { max.x, max.y, min.z };
    vertices[3] = { max.x, min.y, min.z };
    vertices[4] = { min.x, min.y, max.z };
    vertices[5] = { min.x, max.y, max.z };
    vertices[6] = { max.x, max.y, max.z };
    vertices[7] = { max.x, min.y, max.z };

    ImVec2 screenVertices[8];

    for (int i = 0; i < 8; ++i) {
        Vector3 worldPoint = WorldToViewpoint(cam, vertices[i], 2);

        int ScreenWidth = ImGui::GetIO().DisplaySize.x;
        int ScreenHeight = ImGui::GetIO().DisplaySize.y;
        ImVec2 location;
        location.x = ScreenWidth * worldPoint.x;
        location.y = ScreenHeight - worldPoint.y * ScreenHeight;
        checker = checker || (worldPoint.z > 1);
        screenVertices[i] = location;
    }

    for (int i = 0; i < 4; ++i) {
        ImGui::GetBackgroundDrawList()->AddLine(
            screenVertices[i],
            screenVertices[(i + 1) % 4],

            ImColor(0.0f, 184.0f, 194.0f, 0.8f));
        ImGui::GetBackgroundDrawList()->AddLine(
            screenVertices[i + 4],
            screenVertices[((i + 1) % 4) + 4],
            ImColor(0.0f, 184.0f, 194.0f, 0.8f));
        ImGui::GetBackgroundDrawList()->AddLine(
            screenVertices[i],
            screenVertices[i + 4],
            ImColor(0.0f, 184.0f, 194.0f, 0.8f));
    }
}

void drawLineWithStartPoint(ImVec2 startPoint, ImVec2 endPoint, ImU32 color,
                            float thicknes) {
  ImGui::GetForegroundDrawList()->AddLine(startPoint, endPoint, color,
                                          thicknes);
}


void drawCornerBox(float x, float y, float w, float h, ImU32 color,
                   float thickness) {
  int iw = w / 4;
  int ih = h / 4;

  drawLineWithStartPoint(ImVec2(x, y), ImVec2(x + iw, y), color, thickness);
  drawLineWithStartPoint(ImVec2(x, y), ImVec2(x, y + ih), color, thickness);

  drawLineWithStartPoint(ImVec2(x + w - 1, y), ImVec2(x + w - 1, y + ih), color,
                         thickness);
  drawLineWithStartPoint(ImVec2(x + w - 1, y), ImVec2(x + w - iw, y), color,
                         thickness);

  drawLineWithStartPoint(ImVec2(x, y + h), ImVec2(x + iw, y + h), color,
                         thickness);
  drawLineWithStartPoint(ImVec2(x + w - iw, y + h), ImVec2(x + w, y + h), color,
                         thickness);

  drawLineWithStartPoint(ImVec2(x, y + h - ih), ImVec2(x, y + h), color,
                         thickness);
  drawLineWithStartPoint(ImVec2(x + w, y + h - ih), ImVec2(x + w, y + h), color,
                         thickness);
}

void DrawEsp() {
    if (ESPEnable) {
        clearPlayers();
       int enemyCount = 0;
        for (int i = 0; i < players.size(); i++) {
            if (players[i]) {
                void* player = players[i];

if (player != NULL && get_camera() != NULL) {
if (IsLocal(player)) continue;
if (Team(player)) continue;
int health = GetPlayerHealth(player);
int max_health = maxhealth(player);
float HPBarWidth = 70.0f;  // Chiều rộng của thanh máu
float HPBarHeight = 5.5f; 

          auto pos = get_position(get_transform(player));
                Vector3 viewpos = get_position(get_transform(get_camera()));

float distance = Vector3::Distance(viewpos, pos);
            if (distance > Dis) {
                continue;
            }

bool w2sCheck = false;
                ImVec2 top_pos(
                    world2screen_i(pos + Vector3(0, 1.5f, 0))
                );

                ImVec2 bot_pos(
                    world2screen_i(pos + Vector3(0, -0.15f, 0))
                );

                auto pmtXtop = top_pos.x;
                auto pmtXbottom = bot_pos.x;
                if (top_pos.x > bot_pos.x) {
                    pmtXtop = bot_pos.x;
                    pmtXbottom = top_pos.x;
                }

world2screen_c(pos + Vector3(0, 0.75f, 0), w2sCheck);  

                float positionCalc = fabs((top_pos.y - bot_pos.y) * (0.0092f / 0.019f) / 2);

                ImRect rect(
                    ImVec2(pmtXtop - positionCalc, top_pos.y),
                    ImVec2(pmtXbottom + positionCalc, bot_pos.y)
                );

                int distance_scaling = 1;

ImVec2 lineStart = {ImGui::GetIO().DisplaySize.x / 2, 45};
ImVec2 lineEnd = {rect.GetCenter().x, rect.GetCenter().y - 45};




if (w2sCheck) {
                enemyCount++; 
    
    ImVec2 lineStart = {ImGui::GetIO().DisplaySize.x / 2, 45};
    ImVec2 lineEnd = {top_pos.x, rect.Min.y - HPBarHeight - 5}; // Điểm kết thúc nằm trên thanh máu

    // Vẽ đường ESP line
    ImGui::GetBackgroundDrawList()->AddLine(lineStart, lineEnd, ImColor(255, 255, 255), 1.0f);
}



              if (ESPBox) {
          if (boxMode == 0) {
                                ImGui::GetBackgroundDrawList()->AddRect(rect.Min, rect.Max, ImColor(boxColor.x, boxColor.y, boxColor.z, boxColor.w), ESPRounding, 0, 1);
  } else if (boxMode == 1) { //3DBox
                     
bool checker = false;
pos.y += 0.7f;


                                Draw3DBox(pos, Vector3(0.7f, 1.5f, 0.7f), checker);

   } else if (boxMode == 2) { //Conner
                                drawCornerBox(rect.Min.x, rect.Min.y, rect.Max.x - rect.Min.x, rect.Max.y - rect.Min.y, ImColor(boxColor.x, boxColor.y, boxColor.z, boxColor.w), 1.0f);
                            }                                         
                        }

                      
                  

if (ESPHealth) {
    int health = GetPlayerHealth(player); // Giả sử hàm này trả về giá trị sức khỏe hiện tại của người chơi
float healthPercent = static_cast<float>(health) / max_health;
    
    float HPBarWidth = 70.0f;  // Chiều rộng của thanh máu
    float HPBarHeight = 5.5f;  // Chiều cao của thanh máu
    ImColor healthColor = CalculateHealthColor(health, max_health);

    ImVec2 HPBarCenter = ImVec2(rect.GetCenter().x, rect.Min.y - HPBarHeight);
    ImVec2 HPBarTopLeft = ImVec2(HPBarCenter.x - HPBarWidth / 2, HPBarCenter.y - HPBarHeight / 2);
    ImVec2 HPBarBottomRight = ImVec2(HPBarTopLeft.x + (HPBarWidth * healthPercent), HPBarTopLeft.y + HPBarHeight);
    float rounding = HPBarHeight / 2.0f;

    // Vẽ nền của thanh máu (màu đen mờ)
    ImGui::GetBackgroundDrawList()->AddRectFilled(
        ImVec2(HPBarCenter.x - HPBarWidth / 2, HPBarCenter.y - HPBarHeight / 2),
        ImVec2(HPBarCenter.x + HPBarWidth / 2, HPBarCenter.y + HPBarHeight / 2),
        ImColor(0, 0, 0, 110), rounding);

    // Vẽ thanh máu
    ImGui::GetBackgroundDrawList()->AddRectFilled(HPBarTopLeft, HPBarBottomRight, healthColor, rounding);

// Tính vị trí cho text khoảng cách
    float distance = pos.Distance(pos, viewpos);
    ImVec2 distanceTextSize = ImGui::CalcTextSize(std::to_string((int)distance).c_str());

    ImVec2 distanceTextPos = ImVec2(HPBarCenter.x + HPBarWidth / 2 - distanceTextSize.x - 10, HPBarTopLeft.y - distanceTextSize.y + 4);  // vị trí góc phía trên bên phải của thanh máu

    // Vẽ text khoảng cách
    DrawText2(10.0f, distanceTextPos, IM_COL32(255, 255, 255, 255), std::to_string((int)distance).c_str());

    // Vẽ các đoạn máu
    float segmentWidth = HPBarWidth / 3.0f;
    for (int i = 0; i < 3; ++i) {
        float segmentStart = HPBarTopLeft.x + i * segmentWidth;
        float segmentEnd = segmentStart + segmentWidth;
        ImVec2 segmentTopLeft = ImVec2(segmentStart, HPBarTopLeft.y);
        ImVec2 segmentBottomRight = ImVec2(segmentEnd, HPBarTopLeft.y + HPBarHeight);

        // Vẽ từng đoạn máu
        ImGui::GetBackgroundDrawList()->AddRect(segmentTopLeft, segmentBottomRight, ImColor(0, 0, 0), rounding, ImDrawCornerFlags_All, 0.9f);
    }

                }

if (ESPArrow) {

bool checker = false;
                            playerTriangle(ImVec2(top_pos.x, top_pos.y));
                        }

}
}
if (ESPCount) {
    std::string statusText = "" + (enemyCount == 0 ? "Clear" : std::to_string(enemyCount));

    // Tính toán kích thước và vị trí
    ImVec2 textSize = ImGui::CalcTextSize(statusText.c_str());
    ImVec2 boxSize = ImVec2(textSize.x + 30, textSize.y + 10); // Thêm padding cho box
    ImVec2 boxPos = ImVec2(ImGui::GetIO().DisplaySize.x / 2 - boxSize.x / 2, 50); // Căn giữa phía trên

    // Vẽ đổ bóng cho box
    ImGui::GetBackgroundDrawList()->AddRectFilled(boxPos + ImVec2(3, 3), boxPos + boxSize + ImVec2(3, 3), ImColor(30, 30, 30, 180));

    // Vẽ hình chữ nhật nền với gradient
    ImU32 col_bg1 = ImColor(255, 0, 0, 200); // Màu đỏ
    ImU32 col_bg2 = ImColor(255, 165, 0, 200); // Màu cam
    ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(boxPos, boxPos + boxSize, col_bg1, col_bg1, col_bg2, col_bg2);

    // Vẽ viền cho box
    ImGui::GetBackgroundDrawList()->AddRect(boxPos, boxPos + boxSize, IM_COL32_WHITE, 0.0f, 0, 2.0f);

    // Căn giữa chữ trong box
    ImVec2 textPos = ImVec2(boxPos.x + (boxSize.x - textSize.x) / 2, boxPos.y + (boxSize.y - textSize.y) / 2);
    ImGui::GetBackgroundDrawList()->AddText(0, 18.0f, textPos, IM_COL32_WHITE, statusText.c_str());
}

										
            }
        }

    
}