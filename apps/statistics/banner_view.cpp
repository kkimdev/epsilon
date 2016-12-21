#include "banner_view.h"
#include "../constant.h"
#include <assert.h>
#include <poincare.h>

namespace Statistics {

BannerView::BannerView(Data * data) :
  m_intervalView(0.0f, 0.5f),
  m_sizeView(0.0f, 0.5f),
  m_frequencyView(1.0f, 0.5f),
  m_data(data)
{
}

void BannerView::reload() {
  markRectAsDirty(bounds());
  char buffer[k_maxNumberOfCharacters];
  const char * legend = "Interval [";
  int legendLength = strlen(legend);
  strlcpy(buffer, legend, legendLength+1);
  float lowerBound = m_data->selectedBin() - m_data->binWidth()/2;
  int lowerBoundNumberOfChar = Float(lowerBound).convertFloatToText(buffer+legendLength, Constant::FloatBufferSizeInScientificMode, Constant::NumberOfDigitsInMantissaInScientificMode);
  buffer[legendLength+lowerBoundNumberOfChar] = ';';
  float upperBound = m_data->selectedBin() + m_data->binWidth()/2;
  int upperBoundNumberOfChar = Float(upperBound).convertFloatToText(buffer+legendLength+lowerBoundNumberOfChar+1, Constant::FloatBufferSizeInScientificMode, Constant::NumberOfDigitsInMantissaInScientificMode);
  buffer[legendLength+lowerBoundNumberOfChar+upperBoundNumberOfChar+1] = '[';
  buffer[legendLength+lowerBoundNumberOfChar+upperBoundNumberOfChar+2] = 0;
  m_intervalView.setText(buffer);

  legend = "Effectif: ";
  legendLength = strlen(legend);
  strlcpy(buffer, legend, legendLength+1);
  float size = m_data->sizeAtValue(m_data->selectedBin());
  Float(size).convertFloatToText(buffer+legendLength, Constant::FloatBufferSizeInScientificMode, Constant::NumberOfDigitsInMantissaInScientificMode);
  m_sizeView.setText(buffer);

  legend = "Frequence: ";
  legendLength = strlen(legend);
  strlcpy(buffer, legend, legendLength+1);
  float frequency = size/m_data->totalSize();
  Float(frequency).convertFloatToText(buffer+legendLength, Constant::FloatBufferSizeInScientificMode, Constant::NumberOfDigitsInMantissaInScientificMode);
  m_frequencyView.setText(buffer);
}

void BannerView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorWhite);
}

int BannerView::numberOfSubviews() const {
  return 3;
}

View * BannerView::subviewAtIndex(int index) {
  assert(index >= 0);
  if (index == 0) {
    return &m_intervalView;
  }
  if (index == 1) {
    return &m_sizeView;
  }
  return &m_frequencyView;
}

void BannerView::layoutSubviews() {
  KDCoordinate height = bounds().height();
  KDCoordinate width = bounds().width();
  m_intervalView.setFrame(KDRect(0, 0, width, height/2));
  m_sizeView.setFrame(KDRect(0, height/2, width, height/2));
  m_frequencyView.setFrame(KDRect(0, height/2, width, height/2));
}

}