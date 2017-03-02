#ifndef GRAPH_GRAPH_CONTROLLER_H
#define GRAPH_GRAPH_CONTROLLER_H

#include <escher.h>
#include "graph_view.h"
#include "banner_view.h"
#include "curve_parameter_controller.h"
#include "initialisation_parameter_controller.h"
#include "../../shared/interactive_curve_view_controller.h"
#include "../cartesian_function_store.h"

namespace Graph {
class GraphController : public Shared::InteractiveCurveViewController, public Shared::InteractiveCurveViewRangeDelegate {
public:
  GraphController(Responder * parentResponder, CartesianFunctionStore * functionStore, HeaderViewController * header);
  void viewWillAppear() override;
  ViewController * initialisationParameterController() override;

  bool isEmpty() const override;
  const char * emptyMessage() override;

  bool didChangeRange(Shared::InteractiveCurveViewRange * interactiveCurveViewRange) override;
private:
  constexpr static float k_cursorTopMarginRatio = 0.07f;   // (cursorHeight/2)/graphViewHeight
  constexpr static float k_cursorRightMarginRatio = 0.04f; // (cursorWidth/2)/graphViewWidth
  constexpr static float k_cursorBottomMarginRatio = 0.15f; // (cursorHeight/2+bannerHeigh)/graphViewHeight
  constexpr static float k_cursorLeftMarginRatio = 0.04f;  // (cursorWidth/2)/graphViewWidth

  /* When y auto is ticked, we use a display margin to be ensure that the user
   * can move the cursor along the curve without panning the window */
  constexpr static float k_displayTopMarginRatio = 0.09f;
  constexpr static float k_displayBottomMarginRatio = 0.2f;

  constexpr static int k_maxNumberOfCharacters = 8;
  BannerView * bannerView() override;
  bool handleEnter() override;
  void reloadBannerView() override;
  void initRangeParameters() override;
  void initCursorParameters() override;
  bool moveCursorHorizontally(int direction) override;
  bool moveCursorVertically(int direction) override;
  uint32_t modelVersion() override;
  uint32_t rangeVersion() override;
  Shared::InteractiveCurveViewRange * interactiveCurveViewRange() override;
  Shared::CurveView * curveView() override;
  BannerView m_bannerView;
  GraphView m_view;
  Shared::InteractiveCurveViewRange m_graphRange;
  InitialisationParameterController m_initialisationParameterController;
  CurveParameterController m_curveParameterController;
  CartesianFunctionStore * m_functionStore;
  int m_indexFunctionSelectedByCursor;
};

}

#endif
