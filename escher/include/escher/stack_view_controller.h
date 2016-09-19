#ifndef ESCHER_STACK_VIEW_CONTROLLER_H
#define ESCHER_STACK_VIEW_CONTROLLER_H

#include <escher/view_controller.h>
#include <escher/stack_view.h>

constexpr uint8_t kMaxNumberOfStacks = 4;

class StackViewController : public ViewController {
public:
  StackViewController(Responder * parentResponder, ViewController * rootViewController, bool displayFirstStackHeader = false);

  /* Push creates a new StackView and adds it */
  void push(ViewController * vc);
  void pop();


  View * view() override;
  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
private:
  class ControllerView : public View {
  public:
    ControllerView(bool displayFirstStackHeader);
    void setContentView(View * view);
    void pushStack(const char * name);
    void popStack();
  protected:
#if ESCHER_VIEW_LOGGING
  const char * className() const override;
#endif
  private:
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    void layoutSubviews() override;

    StackView m_stackViews[kMaxNumberOfStacks];
    View * m_contentView;
    int8_t m_numberOfStacks;
    bool m_displayFirstStackHeader;
  };

  ControllerView m_view;

  void setupActiveViewController();
  static constexpr uint8_t k_maxNumberOfChildren = 4;
  ViewController * m_children[k_maxNumberOfChildren];
  uint8_t m_numberOfChildren;
  ViewController * m_rootViewController;
};

#endif