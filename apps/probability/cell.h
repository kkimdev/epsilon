#ifndef APPS_PROBABILITY_CELL_H
#define APPS_PROBABILITY_CELL_H

#include <escher.h>

namespace Probability {

class Cell : public TableViewCell {
public:
  Cell();
  void reloadCell() override;
  void setLabel(const char * text);
  void setImage(const Image * image, const Image * focusedImage);
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  constexpr static KDCoordinate k_iconWidth = 35;
  constexpr static KDCoordinate k_iconHeight = 19;
  constexpr static KDCoordinate k_iconMargin = 10;
  constexpr static KDCoordinate k_chevronWidth = 20+8;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void layoutSubviews() override;
  PointerTextView m_labelView;
  ImageView m_iconView;
  const Image * m_icon;
  const Image * m_focusedIcon;
  ChevronView m_chevronView;
};

}

#endif