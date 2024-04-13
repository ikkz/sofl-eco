import { Outlet } from '@modern-js/runtime/router';
import { Provider } from 'jotai';
import { store } from '@/state';

export default function Layout() {
  return (
    <Provider store={store}>
      <Outlet />
    </Provider>
  );
}
